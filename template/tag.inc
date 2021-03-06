<?php require('header.inc');?>
<h2><?php echo esc($view['tag']);?></h2>

<script>
  $(function(){
    $('#target').autocomplete('?action=userlist',{
    formatItem:function(s){return $.escapeHTML(s[0]);}
    });
});
</script>

<div class="center">
  <form method="post">
    <input type="text" id="target" name="target" />
    <input type="submit" value="ユーザにこのタグをつける" />
    <input type="hidden" name="action" value="link" />
    <input type="hidden" name="tag" value="<?php echo esc($view['tag']); ?>" />
  </form>

  <p>
    <?php foreach($view['data'] as $v){?>
    <?php if($v[1] === null){?>
    <div class="tag-piece-min">
      <?php }else{ ?>
      <div class="tag-piece-list">
	<?php } ?>
	<h2>
	  <img src="http://img.tweetimag.es/i/<?php echo urlencode($v[0]); ?>"/><br />
	  <a href="?action=user&user=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a>
	</h2>
	<?php if($v[1] !== null){ ?>
	<div class="desc lfloat"><?php echo esc($v[1]); ?></div>
	<br class="clbr" />
	<?php } ?>
      </div>
      <?php
	 }
	 ?>
      <br class="clbr" />
  </p>
  <?php if(_check()){ ?>
  <div class="com">
    <h2><?php echo esc($_SESSION['screen_name']); ?> の <?php echo esc($view['tag'])?> へのコメント</h2>
    <form method="post">
      <textarea name="content"><?php echo $view['my'][1]; ?></textarea>
      <input type="submit" value="コメントを更新" />
      <input type="hidden" name="action" value="content" />
      <input type="hidden" name="cid" value="<?php echo esc($view['my'][2]); ?>" />
      <input type="hidden" name="tag" value="<?php echo esc($view['tag']); ?>" />
      <input type="hidden" name="screen_name" value="<?php echo esc($_SESSION['screen_name']); ?>" />
    </form>
  </div>
  <?php } ?>
  </div>
  
  <?php require('footer.inc');?>
