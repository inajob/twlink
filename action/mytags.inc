<?php
  // user text
$user = $_SESSION['screen_name'];
$db = dbInit();
$uid = mkUser($db,$user);

$data = array();
$sth = dbq($db,"SELECT" .
	   " tag.name,tag.id,tag_user.uid,tag_user.target,tag_user_content.id" .
	   " FROM tag left join tag_user on tag_user.tid=tag.id and tag_user.target=?" .
	   " left join tag_user_content on tag_user_content.tid=tag.id and tag_user_content.uid=?".
	   " ORDER BY tag.name" , array($uid,$uid));
while($row = $sth->fetch()){
  array_push($data,$row);
 } 
global $view;
$view['data'] = $data;
$view['uid'] = $uid;
$view['uname'] = $user;

$ret = true;
?>