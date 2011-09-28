<?php
  //function dump(){
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
$ret = true;
//  return true;
//}
?>