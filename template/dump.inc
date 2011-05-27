<?php require('header.inc');?>
<p>
<h1>dump</h1>
<table>
<?php foreach($view['data'] as $v){?>
<tr>
  <td><?php echo esc($v[3]); ?></td>
  <td><?php echo esc($v[0]); ?></td>
  <td><?php echo esc($v[1]); ?></td>
  <td><?php echo esc($v[2]); ?></td>
  <td><?php echo esc($v[3]); ?></td>
</tr>
<?php
   }
?>
</table>
<h1>tags</h1>
<table>
<?php foreach($view['tags'] as $v){?>
<tr>
  <td><?php echo esc($v[0]); ?></td>
<?php
   }
?>
</table>


</p>
<?php require('footer.inc');?>
