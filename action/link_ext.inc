<?php
  $tag = $_REQUEST['tag'];
  $target = $_REQUEST['target'];
  
  // バリデーション？
  
  $db = dbInit();
  $ret = ext_tlink($db,$tag,$target,$_SERVER['REMOTE_ADDR']); # bot
?>