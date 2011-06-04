<?php require('header.inc');?>
<?php
    if(isset($view['info'])){
?>
<div><?php echo $view['info']; ?></div>
<?php
    }
?>
<p>
<a href="?action=top">top</a>
</p>
<?php require('footer.inc');?>
