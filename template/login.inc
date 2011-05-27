<?php require('header.inc');?>
<p>
<a href="<?php echo $view["url"] ?>">login</a>
<?php
    if(isset($view['info'])){
?>
<div><?php echo $view['info']; ?></div>
<?php
    }
?>
</p>
<?php require('footer.inc');?>
