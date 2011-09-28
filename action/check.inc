<?php
//function check(){
  if(_check()){
    echo json_encode(array(
			   "user_id" => $_SESSION['user_id'],
			   "screen_name" => $_SESSION['screen_name']
			   ));
  }else{
    echo json_encode(array());
  }
$ret = true;
//}
?>