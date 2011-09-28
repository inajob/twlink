<?php
//function callback(){
//  global $view;
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
$ret = true;
//  return true;
//}
?>