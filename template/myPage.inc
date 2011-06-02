<?php require('header.inc');?>
<p>
<h2><img src="http://img.tweetimag.es/i/<?php echo urlencode($view['name']); ?>" />
  <a href="?action=user&user=<?php echo urlencode($view['name']); ?>"><?php echo esc($view['name']);?></a>
</h2>
<?php
   foreach($view['data'] as $cid => $v){
     if(empty($cid))continue;
     foreach($v['tags'] as $t){
   ?>
<div class="tag">
  <form method="post">
    <h3>
      <a href="?action=tag&tag=<?php echo urlencode($t);?>"><?php echo esc($t);?></a>
    <input type="submit" value="unlink" />
    </h3>
    <input type="hidden" name="action" value="uclink" />
    <input type="hidden" name="tag" value="<?php echo esc($t);?>" />
    <input type="hidden" name="cid" value="<?php echo esc($cid);?>" />
  </form>
</div>
<?php
      }
      ?>
<div class="piece round">
  <form action='action.php' method='post'>
    <div>
      <textarea name="content"><?php echo esc($v['content']); ?></textarea>
    </div>
    <div class="right"><input class="full" type='submit' value='update'></div>
    
    <input type='hidden' name='cid' value='<?php echo esc($cid); ?>' />
    <input type='hidden' name='tag' value='<?php echo esc($v['tags'][0]); //代表どれか一個とればok ?>' />
    <input type='hidden' name='action' value='content' />
  </form>
  <?php if(!empty($v['content'])){ ?>
  <form method="post">
    <select name="tag">
      <?php
	 foreach($view['utags'] as $t){
	    ?>
      <option value="<?php echo esc($t); ?>"><?php echo esc($t); ?></option>
      <?php
	 }
	 ?>
    </select>
    <input type='hidden' name='ptag' value='<?php echo esc($v['tags'][0]); ?>' />
    <input type='hidden' name='action' value='marge' />
    
    <input type="submit" value="marge" />
  </form>
  <?php } ?>
</div>
<?php
   }
   foreach($view['utags'] as $v){
?>
<div class="piece2 round">
  <form action="action.php" method="post">
    <h3><?php echo esc($v); ?></h3>
    <textarea name="content"></textarea>
    <div class="right"><input class="full" type='submit' value='update'></div>
    
    <input type='hidden' name='tag' value='<?php echo esc($v); ?>' />
    <input type='hidden' name='action' value='content' />
  </form>
</div>
<?php
   }
?>
<hr class="clbr" />
<h2>あなたがつけたタグ</h2>
<table>
<?php foreach($view['tags'] as $v){?>
<tr>
  <td><img src="http://img.tweetimag.es/i/<?php echo urlencode($v[2])?>"/></td>
  <td><a href="?action=user&user=<?php echo urlencode($v[2]); ?>"><?php echo esc($v[2]); ?></a></td>
  <td><a href="?action=tag&tag=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a></td>
  <form method="post">
  <td><input type="submit" value="delete"></td>
  <input type="hidden" name="tid" value="<?php echo esc($v[1]); ?>"  />
  <input type="hidden" name="action" value="utlink"  />
  </form>
<?php
   }
?>
</table>


</p>
<?php require('footer.inc');?>
