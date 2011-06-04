<?php
require_once("twitteroauth/twitteroauth.php");
require_once("config.php");

$method = $_REQUEST['action'];

session_start();

function esc($s){
  return htmlspecialchars($s,ENT_QUOTES,"UTF-8");
  #return $s;
}
function dbInit(){
  return new PDO('sqlite:../db/twlink.db');
}

function dbq($db,$sql,$bind=null){
  $sth = $db->prepare($sql);
  if($sth === FALSE){
    error_log("prepare error ".$sql . " " . var_export($db->errorInfo(),true));
  }
  $ret = $sth->execute($bind);
  if($ret === false){
    // log error
    error_log("exuecute error ". $sql . " " . var_export($sth->errorInfo(),true));
  }
  return $sth;
}
function dbe($db,$sql,$bind=null){
  $sth = $db->prepare($sql);
  if($sth === FALSE){
    error_log("prepare error ".$sql . " " . var_export($db->errorInfo(),true));
  }
  $ret = $sth->execute($bind);
  return $ret;
}

function tlink($db, $tag, $target, $user){
  // tag text,target text,user text
  $ret = mkTag($db, $tag, $target);
  $ret2 = mkUser($db, $target);
  $ret3 = mkUser($db, $user);
  if($ret == -1 || $ret2 == -1 )return false;
  $sth = dbq($db, 'SELECT id from tag_user where tid=? AND target=? AND uid=?', array($ret,$ret2,$ret3));
  $rarr = $sth->fetch();
  if($rarr === false){
    $sth = $db->prepare('INSERT INTO tag_user(tid,target,uid) values(?,?,?)');
    $ret3 = $sth->execute(array($ret,$ret2,$ret3));
    return $ret3;
  }
  return true;
}

function utlink($db,$tid){
  $user = mkUser($db, $_SESSION['screen_name']);
  $ret = dbe($db,'DELETE FROM tag_user WHERE tid=? AND uid=?',array($tid,$user));
  return $ret;
}

function clink($db, $tag, $user, $cid){
  $ret = mkTag($db, $tag, $user);  # target -> user 自分に自分でタグをつける
  $ret2 = mkUser($db, $user);
  if($ret == -1 || $ret2 == -1 ){
    error_log("unknown tag or user");
    return false;
  }
  
  $sth = dbq($db,'SELECT id from tag_user_content where tid=? AND uid=?',array($ret,$ret2));
  $rarr = $sth->fetch();
  $sth->closeCursor();
  unset($sth);
  if($rarr === false){
    $ret3 = dbe($db,'INSERT INTO tag_user_content(tid,uid,cid) values(?,?,?)',array($ret,$ret2,$cid));
    error_log(var_export(array($ret,$ret2,$cid),true));
    error_log("success clink ". var_export($ret3,true));
    error_log(var_export($db->errorInfo(),true));
    return $ret3;
  }else{
    error_log("tid:".$ret);
    error_log("uid:".$ret2);
    error_log('already linked');
    return false;
  }

  return false;
}
function uclink($db, $tid, $cid,$uid){
  $ret = dbe($db,'DELETE FROM tag_user_content WHERE cid=? AND tid=? AND uid=?',array($cid,$tid,$uid));
  return $ret;
}
function mkTag($db, $tag){
  $tag = mb_substr($tag,0,64,'UTF-8');  # 制限
  $sth = dbq($db,'SELECT id from tag where name=?',array($tag));
  
  $rarr = $sth->fetch();
  if($rarr === false){
    $ret = dbe($db,'INSERT INTO tag(name) values (?)',array($tag));
    if($ret)$index = $db->lastInsertId();
    else $index = -1;
  }else{
    $index = $rarr[0];
  }
  return $index;
}

function twUserCheck($user){
  // user text
  $to = new TwitterOAuth(TW_CONSUMER_KEY,TW_CONSUMER_SECRET,
			 $_SESSION['oauth_token'],
			 $_SESSION['oauth_token_secret']
			 );
  $line = $to->get("users/show",array("id"=>$user));
  
  if(isset($line->error)){ // not found
    return false;
  }elseif(isset($line->screen_name)){
    return $line->screen_name;
  }else{
    return false; # error
  }
}

function mkUser($db, $user){
  # ユーザーの有無のチェック
  if( ($user = twUserCheck($user)) === false){
    return -1;
  }
  // $user はTwitter名で正規化される
  $sth = dbq($db,'SELECT id from user where name=?',array($user));
  
  $rarr = $sth->fetch();
  if($rarr === false){
    $ret = dbe($db,'INSERT INTO user(name) values (?)',array($user));
    if($ret)$index = $db->lastInsertId();
    else $index = -1;
  }else{
    $index = $rarr[0];
  }
  return $index;
}
function mkContent($db,$content){
  $tag = mb_substr($tag,0,256,'UTF-8');  # 制限
  $ret = dbe($db,"INSERT INTO content(content, updated) values (?, datetime('now', 'localtime'))",array($content));
  if($ret)$index = $db->lastInsertId();
  else $index = -1;
  return $index;
}
function updateContent($db,$cid,$content){
  $ret = dbe($db,'UPDATE content SET content=?'.
	     ' WHERE id=?',
	     array($content,$cid)
	     );
  return $ret;
}


function login(){
  global $view;

  if((!isset($_SESSION['oauth_token']) || $_SESSION['oauth_token']===NULL) &&
     (!isset($_SESSION['oauth_token_secret']) || $_SESSION['oauth_token_secret']===NULL)){
    $to = new TwitterOAuth(TW_CONSUMER_KEY, TW_CONSUMER_SECRET);
    $tok = $to->getRequestToken('http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] . "?action=callback");
    #echo 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] . "?action=callback";
    $_SESSION['request_token'] = $token = $tok['oauth_token'];
    $_SESSION['request_token_secret'] = $tok['oauth_token_secret'];
    
    $view["url"] = $to->getAuthorizeURL($token);
    header("Location: " . $view["url"]);
  }else{
    $view['info'] = 'already login';
  }
  return true;
}
function callback(){
  global $view;
  if((isset($_SESSION['request_token']) && $_SESSION['request_token']!==NULL) &&
     (isset($_SESSION['request_token_secret']) && $_SESSION['request_token_secret']!==NULL) &&
     (isset($_GET['oauth_verifier']) && $_GET['oauth_verifier']) &&
     (!isset($_SESSION['user_id']) || $_SESSION['user_id']===NULL)){
    $title = $_GET['title'];
    $verifier = $_GET['oauth_verifier'];
    $to = new TwitterOAuth(TW_CONSUMER_KEY,TW_CONSUMER_SECRET,$_SESSION['request_token'],$_SESSION['request_token_secret']);
    $access_token = $to->getAccessToken($verifier);

    $_SESSION['oauth_token'] = $access_token['oauth_token'];
    $_SESSION['oauth_token_secret'] = $access_token['oauth_token_secret'];
    #echo var_export($_SESSION,true);
    #echo var_export($access_token,true);
    $_SESSION['user_id'] = $access_token['user_id'];
    $_SESSION['screen_name'] = $access_token['screen_name'];
    
    //ユーザ登録?
    $ret = mkUser(dbInit(), $_SESSION['screen_name']);
/*  デバッグ用
    if($ret==-1){
      echo "user reginster error\n";
    }else{
      echo "user-id: $ret\n";
    }
*/

    $view['info'] = "welcome " . $_SESSION['screen_name'];
    
    // 成功したときは、マイページへリダイレクト
    redirect( "my" );

  }elseif(isset($_SESSION['user_id']) && $_SESSION['user_id'] !== NULL){
    ## ---- RE CALLBACK ---- ( unusual )
    $view['info'] = "reconnect " . $_SESSION['screen_name'];
  }else{
    $view['info'] = "unknown error";
  }
  return true;
}
function logout(){
  session_destroy();

  // ログアウト時は、トップページへリダイレクト
  redirect( "top" );

  return  true;
}

function redirect( $action ){
    header('Location: ' . 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] . "?action=" . $action);
    exit;
}

function tagDump($tag){
  // user text
  #echo "<h1>tag:" . esc($tag) . "</h1>";
  $db = dbInit();
  $sth = dbq($db,"SELECT DISTINCT" .
	     " user.name,content.content" .
	     " FROM user,tag,tag_user".
	     " LEFT JOIN tag_user_content on".
	     " tag_user_content.tid = tag.id AND tag_user_content.uid = user.id".
	     " LEFT JOIN content on".
	     " tag_user_content.cid = content.id".
	     " WHERE user.id=tag_user.target AND tag.id=tag_user.tid AND tag.name=?"
	     ,array($tag));
  $data = array();
  while($row = $sth->fetch()){
    array_push($data,$row);
  } 
  global $view;
  $view['tag'] = $tag;
  $view['data'] = $data;
}

function userDump($user){
  // user text

  $db = dbInit();
  $sth = dbq($db,"SELECT DISTINCT" .
	     " tag.name,content.content" .
	     " FROM user,tag,tag_user".
	     " LEFT JOIN tag_user_content on".
	     " tag_user_content.tid = tag.id AND tag_user_content.uid = user.id".
	     " LEFT JOIN content on".
	     " tag_user_content.cid = content.id".
	     " WHERE user.id=tag_user.target AND tag.id=tag_user.tid AND user.name=?".
	     " ORDER BY content.id desc"
	     ,array($user));

  $data = array();
  while($row = $sth->fetch()){
    array_push($data,$row);
  } 
  global $view;
  $view['data'] = $data;
  $view['user'] = $user;
}
function usersDump(){
  // user text
  $db = dbInit();
  $sth = dbq($db,"SELECT" .
	     " name" .
	     " FROM user");
  $data = array();
  while($row = $sth->fetch()){
    array_push($data,$row);
  } 
  global $view;
  $view['data'] = $data;
}

function tagsDump(){
  // user text
  $db = dbInit();
  $data = array();
  $sth = dbq($db,"SELECT" .
	     " name,count(tag_user.id)" .
	     " FROM tag left join tag_user on tag_user.tid=tag.id group by tag.id");
  while($row = $sth->fetch()){
    array_push($data,$row);
  } 
  global $view;
  $view['data'] = $data;
}

function myDump(){
  // user text
  $user = $_SESSION['screen_name'];
  $db = dbInit();
  $uid = mkUser($db,$user);
  $sth = dbq($db,"SELECT DISTINCT" .
	     " tag.name, content.content, content.id" .
	     " FROM user,tag,tag_user".
	     " LEFT JOIN tag_user_content on".
	     " tag_user_content.tid = tag.id AND tag_user_content.uid = user.id".
	     " LEFT JOIN content on".
	     " tag_user_content.cid = content.id".
	     " WHERE user.id=tag_user.target AND tag.id=tag_user.tid AND user.id=?".
	     " ORDER BY content.id desc"
	     ,array($uid));
  $data = array();
  $undesctag = array();
  while($row = $sth->fetch()){
    if(!isset($data[$row[2]]) || $row[1]==''){
      $data[$row[2]] = array('tags' => array($row[0]), 'content' => $row[1]);
    }else{
      array_push($data[$row[2]]['tags'], $row[0]);
    }
    if(empty($row[1])){
      array_push($undesctag, $row[0]);
    }
  } 

  $tags = array();
  $sth = dbq($db,
	     'select tag.name,tag.id,user.name from tag,tag_user,user where user.id=tag_user.target AND tag_user.uid=? AND tag_user.tid=tag.id',
	     array($uid));
  while($row = $sth->fetch()){
    array_push($tags,$row);
  }

  global $view;
  $view['utags'] = $undesctag;
  $view['data'] = $data;
  $view['tags'] = $tags;
  $view['name'] = $user;
}

function dump(){
  $db = dbInit();
  $sth = dbq($db,"SELECT" .
	     " u2.name,tag.name,u.name,tag_user.id" .
	     " FROM user AS u,user AS u2,tag,tag_user".
	     " WHERE u.id=tag_user.uid AND tag.id=tag_user.tid AND u2.id=tag_user.target"
	     );
  $data = array();
  while($row = $sth->fetch()){
    array_push($data,array(esc($row[0]),esc($row[1]),esc($row[2]),esc($row[3])));
  }

  $tags = array();
  $sth = dbq($db, 'select name from tag');
  while($row = $sth->fetch()){
    array_push($tags,$row);
  }
  global $view;
  $view['data'] = $data;
  $view['tags'] = $tags;
  #echo "<p><a href='twlink.html'>go</a></p>";
  return true;
}

function check(){
  if(_check()){
    echo json_encode(array(
			   "user_id" => $_SESSION['user_id'],
			   "screen_name" => $_SESSION['screen_name']
			   ));
  }else{
    echo json_encode(array());
  }
}
function _check(){
  if(isset($_SESSION['user_id']) && $_SESSION['user_id'] !== NULL){
    return true;
  }else{
    return false;
  }

}
// ==============================
function tagsPage(){
  tagsDump();
  return true;
}
function usersPage(){
  usersDump();
  return true;
}
function tagPage(){
  $tag = $_GET['tag'];
  tagDump($tag);
  return true;
}
function userPage(){
  $user = $_GET['user'];
  userDump($user);
  return true;
}
function myPage(){
  $db = dbInit();
  myDump();
  return true;
}
function contentPage(){
     $tag = $_REQUEST['tag'];
     $user = $_SESSION['screen_name'];
     $content = $_REQUEST['content'];
     $cid = $_REQUEST['cid'];
     $db = dbInit();
     if(empty($cid)){
       $cid = mkContent($db,$content);
       error_log('contentPage: '.$cid.' '.$tag.' '.$user);
       clink($db, $tag,$user,$cid);
       $ret = true; # todo: ok?
     }else{
       if(empty($content)){
	 $ret = dbe($db,'DELETE FROM tag_user_content where cid=?',array($cid));
	 $ret = dbe($db,'DELETE FROM content where id=?',array($cid));
       }else{
	 $ret = updateContent($db,$cid,$content);
       }
     }
     return $ret;
}
function linkPage(){
  $tag = $_POST['tag'];
  $target = $_POST['target'];
  
  // バリデーション？
  
  $db = dbInit();
  $res = tlink($db,$tag,$target,$_SESSION['user_id']);
  return $res;
}
function utlinkPage(){
  $tid = $_POST['tid'];
  $db = dbInit();
  $ret = utlink($db,$tid);
  return $ret;
}

function uclinkPage(){
  $db = dbInit();
  $tid = mkTag($db,$_REQUEST['tag']);
  $cid = $_REQUEST['cid'];
  $uid = mkUser($db,$_SESSION['screen_name']);
  return uclink($db,$tid,$cid,$uid);
}

function topPage(){
  tagsDump();
  return true;
}

function followerPage(){
  $to = new TwitterOAuth(TW_CONSUMER_KEY,TW_CONSUMER_SECRET,
			 $_SESSION['oauth_token'],
			 $_SESSION['oauth_token_secret']
			 );
  $user = $_SESSION['screen_name'];
  $line = $to->get("statuses/followers",array("screen_name"=>$user));
  $data = array();
  foreach($line as $i){
    array_push($data,array($i->screen_name,$i->status->text));
  }
  global $view;
  
  $view['user'] = $user;
  $view['data'] = $data;
  return true;
}

function friendPage(){
  $to = new TwitterOAuth(TW_CONSUMER_KEY,TW_CONSUMER_SECRET,
			 $_SESSION['oauth_token'],
			 $_SESSION['oauth_token_secret']
			 );
  $user = $_SESSION['screen_name'];
  $line = $to->get("statuses/friends",array("screen_name"=>$user));
  $data = array();
  foreach($line as $i){
    array_push($data,array($i->screen_name,$i->status->text));
  }
  global $view;
  
  $view['user'] = $user;
  $view['data'] = $data;
  return true;
}

function margePage(){
  $db = dbInit();
  $tid = mkTag($db, urldecode($_REQUEST['tag']));
  $pid = mkTag($db, urldecode($_REQUEST['ptag']));
  $user = $_SESSION['screen_name'];
  $uid = mkUser($db, $user);
  error_log(var_export($_REQUEST,true));

  $sth = dbq($db, 'SELECT id,cid from tag_user_content where uid=? AND tid=?',array($uid, $tid));
  $row = $sth->fetch();
  $sth->closeCursor();

  $sth = dbq($db, 'SELECT id,cid from tag_user_content where uid=? AND tid=?',array($uid, $pid));
  $row2 = $sth->fetch();
  $sth->closeCursor();

  unset($sth);
  
  if($row !== false){
    error_log("tid content is not null");
    return false;
  }
  error_log(var_export(array($row,$row2),true));
  if($row2 === false){
    $cid = mkContent($db, 'blank');
  }else{
    $cid = $row2[1];
  }
  error_log('cid:'.$cid);
  error_log('tag:'.$_REQUEST['tag']);
  return clink($db, $_REQUEST['tag'], $user, $cid);
}

//=======================================-
function mkPage($fname,$login,$red,$title){
  return array(
	       'func' => $fname,
	       'login' => $login,
	       'red'   => $red,
	       'title' => $title
	       );
}



###############################
## DISPATCHER
###############################
$route=array(
	     'login'    => mkPage('login'        ,false,false,'ログイン'), //
	     'callback' => mkPage('callback'     ,false,false,'ログイン完了'), // r
	     'logout'   => mkPage('logout'       ,false ,false,'ログアウト'), // 
	     'check'    => mkPage('check'        ,false,false,''), // api
	     'tags'     => mkPage('tagsPage'     ,false,false,'タグ一覧'), // 
	     'users'    => mkPage('usersPage'    ,false,false,'ユーザ一覧'), // 
	     'tag'      => mkPage('tagPage'      ,false,false,'タグ情報'), // 
	     'user'     => mkPage('userPage'     ,false,false,'ユーザ情報'), // 
	     'my'       => mkPage('myPage'       ,true ,false,'マイページ'), // 
	     'content'  => mkPage('contentPage'  ,true ,true ,''), // r
	     'dump'     => mkPage('dump'         ,false,false,'ダンプ'), // 
	     'link'     => mkPage('linkPage'     ,true ,true ,''), // r
	     'utlink'   => mkPage('utlinkPage'   ,true ,true ,''),  // r
	     'top'      => mkPage('topPage'      ,false,false,'トップ'),  //
	     'follower' => mkPage('followerPage' ,false,false,'フォロワー'),  //
	     'friend'   => mkPage('friendPage'   ,true,false,'友達'),  //
	     'marge'    => mkPage('margePage'    ,true,true,''),  //
	     'uclink'   => mkPage('uclinkPage'   ,true,true,'')  //
	     );
$view = array();

if(isset($route[$method])){
  $logined = _check();
  if($route[$method]['login']==false || $logined){

    global $view;
    $view['title'] = $route[$method]['title'];
    $ret = call_user_func($route[$method]['func']);

    if($route[$method]['red']===false){
      #echo $view['title'];
      include('../template/'.$route[$method]['func']. '.inc');
    }
    #echo var_export($ret,true) . "\n";
    #echo $route[$method]['red'] . "\n";
    #echo $logined . "\n";
    #echo $_SESSION['redirect'];
    if($ret){
      if($route[$method]['red'] === true){
	if($logined){
	  if(isset($_SESSION['redirect'])){
	    header("Location: " . $_SESSION['redirect']);
	    unset($_SESSION['redirect']);
	  }else{
	    header("Location: " . 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] ."?action=top");
	  }
	}else{
	  echo "please login2";
	}
      }
    }else{
      $view['info'] =  "error";
      include('../template/error.inc');
    }
    
    if($route[$method]['red'] === false && $logined){
      $_SESSION['redirect'] = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] . '?' . $_SERVER["QUERY_STRING"];
    }
  }else{
    global $view;
    $view['info'] = "please login";
    include('../template/error.inc');
  }
 }else{
  global $view;
  $view['info'] = "invalid request";
  include('../template/error.inc');
}

/*
switch($method){
 case 'login':
   login();
   break;
 case 'callback':
   callback();
   break;
 case 'logout':
   logout();
   break;
 case 'check':
   check();
   break;
 case 'tags':
   tagsDump();
   break;
 case 'users':
   usersDump();
   break;
 case 'tag':
   $tag = $_GET['tag'];
   tagDump($tag);
   break;
 case 'user':
   $user = $_GET['user'];
   userDump($user);
   break;
 case 'my':
   if(_check()){
     $db = dbInit();
     myDump();
   }else{
     echo "please login";
   }
   break;
 case 'contents':
   if(_check()){
     $tag = $_REQUEST['tag'];
     $user = $_SESSION['screen_name'];
     $content = $_REQUEST['content'];

     $db = dbInit();
     clink($db, $tag,$user,$content);
     echo "ok write";
   }else{
     echo "please login";
   }
   break;
 case 'dump':
   dump();
   break;
 case 'link':
   if(_check()){
     $tag = $_POST['tag'];
     $target = $_POST['target'];
     
     // バリデーション？
     
     $db = dbInit();
     $res = tlink($db,$tag,$target,$_SESSION['user_id']);
     
     if($res){
       echo "ok";
     }else{
       echo "ng";
     }
   }else{
     echo "please login.";
     echo "<p><a href='twlink.html'>go</a></p>";
   }
   break;
 case 'utlink':
   $id = $_POST['id'];
   if(_check()){
     $db = dbInit();
     $ret = utlink($db,$id);
     if($res!==false){
       echo "ok";
     }else{
       echo "ng";
     }
   }else{
     echo "please login.";
     echo "<p><a href='twlink.html'>go</a></p>";     
   }
   break;
 }
*/
?>
