<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja" lang="ja">
   <head>
   <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
   <meta name="viewport" content="width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;">
   <title>twlink</title>
   <style><!--
   *{
 margin:0px;
 padding:0px;
 }
   p{
   margin:1em;
   }
.desc ul{
  margin-left:1em;
}
.desc h1{
  font-size:large;
}
.desc h2{
  font-size:medium;
}
.desc h3{
  font-size:small;
}

   div.login{
   text-align:right;
     padding-right:1em;
   background-color:#ddf;
 }
.halfloat{
  float:left;
   width:50%;
 }
.round{
  border-radius: 10px;/* CSS3草案 */
  -webkit-border-radius: 10px;/* Safari,Google Chrome用 */
     -moz-border-radius: 10px;/* Firefox用 */
 }
.piece{
  background-color:#dfd;
  margin:0.2em;
   padding:0.2em;
   border:solid 2px;
 }
.piece2{
  background-color:#ff9;
  margin:0.2em;
   padding:0.2em;
   border:solid 2px;
 }
div.main{
 margin:0.1em;
 padding:1em;
  background-color:#ddd;
}
td{
 padding:0.3em;
 border:solid black 1px;
}
   div.footer{
     text-align:right;
   }
textarea{
 width:98%;
 height:240px;
}
.center{
  text-align:center;
}
.tag{
 padding:0.2em;
 border:solid 1px;
  float:left;
 margin:3px;
  word-break: break-all;
  background-color:white;
 }
.tags{
  font-size:large;
 padding:0.5em;
 }
.tags .name{
  background-color:#9dd;
  font-size:x-large;
 }
.tag-piece h2.name{
  text-align:left;
 }
.tag-piece-min h2{
  font-size:small;
 }
.tag-piece{
  background-color:#dfd;
  border:solid 1px;
  text-align:left;
 margin:0.5em;
 padding:0em;
  word-break: break-all;
 width:80%;
 }
.desc{
  background-color:white;
 padding:0.5em;
 }
.lfloat{
  float:left;
}
.desc h2{ 
  text-align:left;  
}
.desc h2{ 
  text-align:left;  
}
.tag-piece-min{
  float:left;
  border:solid 1px;
 margin:0.1em;
 padding:0.1em;
    text-align:left;
    /*width:30%;*/
  word-break: break-all;
 }
.tag-piece-list{
  /*float:left;*/
  border:solid 1px;
 margin:0.1em;
 padding:0.1em;
    text-align:left;
    /*width:30%;*/
  word-break: break-all;
 }
.tag-piece-list h2{
  float:left;
}

.descw{
    word-break: break-all;
    background-color:white;
 }

div.bar{
  background-color:#ddf;
  padding-left:1em;
}
.com{
  background-color:#dff;
  padding:1em;
 }
h2{
  text-align:center;
}
img.half{
 width:24px;
 height:24px;
}
.small{
  font-size:small;
 }
.full{
 width:100%;
 }
.right{
  text-align:right;
 }
.clbr{
 clear:both;
 }
.msg{
  font-size:small;
 margin:1em;
 padding:1em;
  background-color:white;
 }
.center{
  text-align:center;
  margin-left:auto;
  margin-right:auto;
 width:100%;
 }

   --></style>
   <script src="jquery-1.6.1.min.js"></script>
   <script src="wiki.js"></script>
<!-- マジック これ怖いかな？ -->
<script>
<!--
$(function(){
    $(".desc").each(function(e){
	var wiki = new WikiParser();
	var s = this.innerHTML;
	$(this).text("");
	wiki.parse(s,this);
      });
    
  })
-->
</script>

  </head>
  <body>
    <h1><a href="?action=top">twlink</a></h1>
   <div class="login">
   <?php
  if(session_id()==="" || _check()){
     echo '<a href="action.php?action=logout">logout</a>';
   }else{
     echo '<a href="action.php?action=login">login</a>';
   }
   ?>
      </div>
<div class="bar">
<!--  <a href="action.php?action=follower">follower</a> -->
  <a href="action.php?action=friend">friend</a>
  <a href="action.php?action=my">my</a>
<!--  <a href="action.php?action=users">users</a>-->
<!--  <a href="action.php?action=tags">tags</a>-->
</div>
  <h2><?php echo esc($view['title']); ?></h2>

<div class="main">