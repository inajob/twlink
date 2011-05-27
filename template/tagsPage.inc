<?php require('header.inc');?>
<p>
<table>
<?php foreach($view['data'] as $v){?>
<tr>
     <td><a href="?action=tag&tag=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a></td>
</tr>
<?php
   }
?>
</table>


</p>
<?php require('footer.inc');?>
