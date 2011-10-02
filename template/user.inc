<?php require('header.inc');?>

<script>
<!--
    $(function(){
    // on start
    
    $('#tag').autocomplete('?action=taglist',{
    formatItem:function(s){return $.escapeHTML(s[0]);}
    });
    
    });

    function autoInput(id,s){
    var d = document.getElementById(id);
    d.value = s;
    d.focus();
    }

/*
    $(function(){
    var im = $('#icon');
    var timer = null;
    $('#target').bind('keyup',function(e){
    if(timer != null)clearTimeout(timer);
    timer = setTimeout(function(){
    timer = null;
    var s = e.target.value;
    icon.src= 'http://img.tweetimag.es/i/'+s;
    },250);
    });
    });
*/
-->
</script>

<div class="center">
  <h2>
    <img src="http://img.tweetimag.es/i/<?php echo urlencode($view['user']); ?>"/>
    <a href="?action=user&user=<?php echo urlencode($view['user']); ?>"><?php echo esc($view['user']);?></a>
  </h2>
  <a href="https://twitter.com/<?php echo urlencode($view['user']); ?>" class="twitter-follow-button" data-show-count="false">Follow @<?php echo esc($view['user']); ?></a>
  <script src="http://platform.twitter.com/widgets.js" type="text/javascript"></script>
</div>

<div class="center">
  <p>
    <form method="post">
      <input type="text" id="tag" name="tag" />
      <input type="submit" value="タグ登録" />
      <input type="hidden" name="action" value="link" />
      <input type="hidden" name="target" value="<?php echo esc($view['user']); ?>" />
    </form>
  </p>
  
  <?php foreach($view['data'] as $v){?>
  <div class="<?php
if($v['content']===null){
echo 'tag-piece-min';
}else{
echo 'tag-piece';
}
?>">
<div class="tags">
<?php
foreach($v['tags'] as $name){
?>
    <span class="name"><a href="?action=tag&tag=<?php echo urlencode($name); ?>"><?php echo esc($name); ?></a></span>
<?php
  }
?>
</div>
				     <?php if($v['content'] !== null){?>
    <div class="desc"><?php echo esc($v['content']); ?></div>
						   <?php } ?>
  </div>
  <?php
       }
       ?>
  <br class="clbr" />
</div>
<?php require('footer.inc');?>
