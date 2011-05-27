<?php require('header.inc');?>
<p>
<h2><img src="http://img.tweetimag.es/i/<?php echo urlencode($view['user']); ?>"/>
    <a href="?action=user&user=<?php echo urlencode($view['user']); ?>"><?php echo esc($view['user']);?></a>
</h2>
<table>
<?php foreach($view['data'] as $v){?>
<tr>
  <td><img class="half" src="http://img.tweetimag.es/i/<?php echo urlencode($v[0]); ?>"/></td>
  <td><a href="?action=user&user=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a>
    <a href="http://twitter.com/<?php echo urlencode($v[0]); ?>" target="_blank">[t]</a>
  </td>
  <td><div class="small"><?php echo esc($v[1]); ?></div></td>
</tr>
<?php
   }
?>
</table>


</p>
<?php require('footer.inc');?>
