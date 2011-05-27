<?php require('header.inc');?>
<p>
<h2><img src="http://img.tweetimag.es/i/<?php echo urlencode($view['name']); ?>" />
  <a href="?action=user&user=<?php echo urlencode($view['name']); ?>"><?php echo esc($view['name']);?></a>
</h2>
<?php
   $pre = -1;
   foreach($view['data'] as $v){
   if(!empty($v[2]) && $pre == $v[2]){
   ?>
<form method="post">
  <a href="?action=tag&tag=<?php echo urlencode($v[0]);?>"><?php echo esc($v[0]);?></a>
  <input type="submit" value="unlink" />
  <input type="hidden" name="action" value="uclink" />
  <input type="hidden" name="tag" value="<?php echo esc($v[0]);?>" />
  <input type="hidden" name="cid" value="<?php echo esc($v[2]);?>" />
</form>
<?php
}else{
      ?>
<div class="piece">  
  <form action='action.php' method='post'>
    <h3>
      <a href="?action=tag&tag=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a>
    </h3>
    <div>
      <textarea name='content'><?php echo esc($v[1]); ?></textarea>
    </div>
    <div class="right"><input type='submit' value='update'></div>
    
    <input type='hidden' name='cid' value='<?php echo esc($v[2]); ?>' />
    <input type='hidden' name='tag' value='<?php echo esc($v[0]); ?>' />
    <input type='hidden' name='action' value='content' />
  </form>
  <?php if(!empty($v[1])){ ?>
  <form method="post">
    <select name="tag">
      <?php
	 foreach($view['data'] as $t){
	 if($t != $v && empty($t[1])){
	    ?>
      <option value="<?php echo esc($t[0]); ?>"><?php echo esc($t[0]); ?></option>
      <?php
	 }
	 }
	 ?>
    </select>
    <input type='hidden' name='ptag' value='<?php echo esc($v[0]); ?>' />
    <input type='hidden' name='action' value='marge' />
    
    <input type="submit" value="marge" />
  </form>
  <?php } ?>
</div>
<?php
   }
   $pre = $v[2];
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
