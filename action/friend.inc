<?php
  //function friendPage(){
  $to = new TwitterOAuth(TW_CONSUMER_KEY,TW_CONSUMER_SECRET,
			 $_SESSION['oauth_token'],
			 $_SESSION['oauth_token_secret']
			 );
  $user = $_SESSION['screen_name'];
  $line = $to->get("statuses/friends",array("screen_name"=>$user));
  $data = array();
  foreach($line as $i){
    array_push($data,array($i->screen_name,$i->status->text));
  }
  global $view;
  
  $view['user'] = $user;
  $view['data'] = $data;
$ret = true;
//  return true;
//}

?>