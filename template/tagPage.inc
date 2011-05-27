<?php require('header.inc');?>
<h2><?php echo esc($view['tag']);?></h2>

<div class="center">
  <form method="post">
    <input type="text" name="target" />
    <input type="submit" value="ユーザにこのタグをつける" />
    <input type="hidden" name="action" value="link" />
    <input type="hidden" name="tag" value="<?php echo esc($view['tag']); ?>" />
  </form>

  <p>
    <?php foreach($view['data'] as $v){?>
    <div class="tag-piece-min">
      <h2>
	<img src="http://img.tweetimag.es/i/<?php echo urlencode($v[0]); ?>"/>
	<a href="?action=user&user=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a>
      </h2>
      <div class="desc"><?php echo esc($v[1]); ?></div>
    </div>
    <?php
       }
       ?>
    <br class="clbr" />
  </p>
</div>

<?php require('footer.inc');?>
