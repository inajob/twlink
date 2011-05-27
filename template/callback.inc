<?php require('header.inc');?>
<p>
<div>
login success
</div>
<a href="?action=top">top</a>
<?php
    if(isset($view['info'])){
?>
<div><?php echo $view['info']; ?></div>
<?php
    }
?>
</p>
<?php require('footer.inc');?>
