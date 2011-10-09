<?php
  // user text
$user = $_SESSION['screen_name'];
$db = dbInit();
$uid = mkUser($db,$user);

$data = array();
$sth = dbq($db,"SELECT" .
	   " tag.name,".         # 0
	   "tag.id,".            # 1
	   "tag_user.uid,".      # 2
	   "tag_user.target,".   # 3
	   "tag_user_content.id".# 4
	   " FROM tag left join tag_user on tag_user.tid=tag.id and tag_user.target=?" .
	   " left join tag_user_content on tag_user_content.tid=tag.id and tag_user_content.uid=?".
	   " ORDER BY tag.name" , array($uid,$uid));

$tags_content = array();
$tags_verified = array();
$tags_not_verified = array();
$tags_none = array();
while($row = $sth->fetch()){
  array_push($data,$row);
  if(empty($row[4])){
    if($row[3] == $uid){ // target === myid
      if($row[2] == $uid){ // uid === myid
	array_push($tags_verified, $row);
      }else{
	array_push($tags_not_verified, $row);
      }
    }else{
      array_push($tags_none, $row);
    }
  }else{
    array_push($tags_content, $row);
  }
 } 
global $view;
$view['data'] = $data;
$view['tags_verified'] = $tags_verified;
$view['tags_not_verified'] = $tags_not_verified;
$view['tags_none'] = $tags_none;
$view['tags_content'] = $tags_content;

$view['uid'] = $uid;
$view['uname'] = $user;

$ret = true;
?>