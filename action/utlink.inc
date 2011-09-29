<?php
  $tid = $_POST['tid'];

  $db = dbInit();
  $user = mkUser($db, $_SESSION['screen_name']);

  $ret = dbe($db,'DELETE FROM tag_user WHERE tid=? AND uid=?',array($tid,$user));

//  return $ret;
?>