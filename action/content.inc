<?php
//function contentPage(){
     $tag = $_REQUEST['tag'];
     $user = $_SESSION['screen_name'];
     $content = $_REQUEST['content'];
     $cid = $_REQUEST['cid'];
     $db = dbInit();
     if(empty($cid)){
       $cid = mkContent($db,$content);
       error_log('contentPage: '.$cid.' '.$tag.' '.$user);
       clink($db, $tag,$user,$cid);
       $ret = true; # todo: ok?
     }else{
       if(empty($content)){
	 $ret = dbe($db,'DELETE FROM tag_user_content where cid=?',array($cid));
	 $ret = dbe($db,'DELETE FROM content where id=?',array($cid));
       }else{
	 $ret = updateContent($db,$cid,$content);
       }
     }
//     return $ret;
//}

?>