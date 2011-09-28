<?php
  //function uclinkPage(){
  $db = dbInit();
  $tid = mkTag($db,$_REQUEST['tag']);
  $cid = $_REQUEST['cid'];
  $uid = mkUser($db,$_SESSION['screen_name']);
  $ret =  uclink($db,$tid,$cid,$uid);
//}
?>