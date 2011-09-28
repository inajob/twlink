<?php
  //function linkPage(){
  $tag = $_POST['tag'];
  $target = $_POST['target'];
  
  // バリデーション？
  
  $db = dbInit();
  $res = tlink($db,$tag,$target,$_SESSION['user_id']);
$ret = $res;
//  return $res;
//}
?>