<?php require('header.inc');?>
<p>
<table>
<?php foreach($view['data'] as $v){?>
<tr>
     <td><img src="http://img.tweetimag.es/i/<?php echo urlencode($v[0]); ?>"/></td>
     <td><a href="?action=user&user=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a></td>
</tr>
<?php
   }
?>
</table>


</p>
<?php require('footer.inc');?>
