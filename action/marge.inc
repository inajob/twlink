<?php
  //function margePage(){
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
    $ret = false;
    //return false;
  }else{
    error_log(var_export(array($row,$row2),true));
    if($row2 === false){
      $cid = mkContent($db, 'blank');
    }else{
      $cid = $row2[1];
    }
    error_log('cid:'.$cid);
    error_log('tag:'.$_REQUEST['tag']);
    $ret =  clink($db, $_REQUEST['tag'], $user, $cid);
  }

  //}
?>