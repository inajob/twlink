<?php require('header.inc');?>
<?php
function tagged($v){
   global $view;
   echo '<td>' . esc($v[0]) .'::'.$v[4]. '</td>';
   ?>
<td>
  <form class="inline" method="post">
    <input type="submit" value="自分にタグをつける">
    <input type="hidden" name="tag" value="<?php echo esc($v[0]) ?>">
    <input type="hidden" name="target" value="<?php echo esc($view['uname']) ?>">
    <input type="hidden" name="action" value="link">
  </form>
</td>
<?php
   }
?>

<?php
function untagged($v){
   global $view;
   echo "<td>" . esc($v[0]) .'::'.$v[4] . "</td>";
   ?>
<td>
  <form class="inline" method="post">
    <input type="submit" value="タグを外す">
    <input type="hidden" name="tid" value="<?php echo esc($v[1]) ?>">
    <input type="hidden" name="action" value="utlink">
  </form>
</td>
<?php
   }
?>

<table>
<?php foreach($view['data'] as $v){ ?>
<?php   
if($v[3] == $view['uid'] || !empty($v[4])){ // target === myid
if($v[2] == $view['uid'] || !empty($v[4])){ // uid    === myid
?>
<tr><td>[my-tagged]</td>
  <?php untagged($v); ?>
</tr>
<?php }else{ ?>
<tr><td>[n-tagged]</td>
  <?php tagged($v); ?>
</tr>
<?php
}
}else{
/*
?>
<tr><td>[un-tagged]</td>
  <?php tagged($v); ?>
</tr>
<?php
*/
}
?>
<?php } ?>
</table>
<?php require('footer.inc');?>
