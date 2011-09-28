<?php
  //function logout(){
  session_destroy();

  // ログアウト時は、トップページへリダイレクト
  redirect( "top" );

$ret = true;
//  return  true;
//}
?>
