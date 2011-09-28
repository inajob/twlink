<?
//function login(){
//  global $view;

  if((!isset($_SESSION['oauth_token']) || $_SESSION['oauth_token']===NULL) &&
     (!isset($_SESSION['oauth_token_secret']) || $_SESSION['oauth_token_secret']===NULL)){
    $to = new TwitterOAuth(TW_CONSUMER_KEY, TW_CONSUMER_SECRET);
    $tok = $to->getRequestToken('http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] . "?action=callback");
    #echo 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'] . "?action=callback";
    $_SESSION['request_token'] = $token = $tok['oauth_token'];
    $_SESSION['request_token_secret'] = $tok['oauth_token_secret'];
    
    $view["url"] = $to->getAuthorizeURL($token);
    header("Location: " . $view["url"]);
  }else{
    $view['info'] = 'already login';
  }
$ret = true;
//  return true;
//}

?>