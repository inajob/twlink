<?php require('header.inc');?>
<script>
<!--
    $(function(){
    // on start
    
    $('#tag').autocomplete('?action=taglist',{
    formatItem:function(s){return $.escapeHTML(s[0]);}
    });
    
    });

    function autoInput(id,s){
    var d = document.getElementById(id);
    d.value = s;
    d.focus();
    }
-->
</script>
<?php
function printTag($name){
   return '<a href="?action=tag&tag=' . urlencode($name) . '">' . esc($name) . '</a>';
}
function printTag2($name){
   global $view;
   return
   '<form class="inline" method="post">'.
    '<input type="submit" value="' . urlencode($name) . '">'.
    '<input type="hidden" name="tag" value="' . urlencode($name) . '">'.
    '<input type="hidden" name="target" value="' . urlencode($view['uname']) . '">'.
    '<input type="hidden" name="action" value="link">'.
  '</form>';
}
function tagged($v){
   global $view;
   echo '<div class="tag">' . printTag($v[0]) . '';
   ?>
  <form class="inline" method="post">
    <input type="submit" value="自分にタグをつける">
    <input type="hidden" name="tag" value="<?php echo esc($v[0]) ?>">
    <input type="hidden" name="target" value="<?php echo esc($view['uname']) ?>">
    <input type="hidden" name="action" value="link">
  </form>
</div>
<?php
   }
?>

<?php
function untagged($v){
   global $view;
   echo "<div class='tag'>" . printTag($v[0]) . "";
   ?>
  <form class="inline" method="post">
    <input type="submit" value="タグを外す">
    <input type="hidden" name="tid" value="<?php echo esc($v[1]) ?>">
    <input type="hidden" name="action" value="utlink">
  </form>
</div>
<?php
   }
?>

<div class="center">
  <h2>
    <img src="http://img.tweetimag.es/i/<?php echo urlencode($view['uname']); ?>"/>
    <a href="?action=user&user=<?php echo urlencode($view['uname']); ?>"><?php echo esc($view['uname']);?></a>
  </h2>
</div>


<div class="center">
  <p>
    <form method="post">
      <input type="text" id="tag" name="tag" />
      <input type="submit" value="タグ登録" />
      <input type="hidden" name="action" value="link" />
      <input type="hidden" name="target" value="<?php echo esc($view['user']); ?>" />
    </form>
  </p>

  <h2 class="top">記事付きタグ</h2>
  <p>
    あなたが記事を作成したタグです。
    消す場合はまず記事を消してください。
  </p>
  <?php foreach($view['tags_content'] as $v){
	echo '<div class="tag">' . printTag($v[0]) . '</div>';
	} ?>
  <br class="clbr">

  <h2 class="top">承認タグ</h2>
  <p>
    あなたが付けたタグです。
  </p>
  <?php foreach($view['tags_verified'] as $v){ ?>
  <?php untagged($v); ?>
  <?php } ?>
  <br class="clbr">
  <h2 class="top">未承認タグ</h2>
  <p>
    誰かがあなたにつけたタグです
  </p>
  <?php foreach($view['tags_not_verified'] as $v){ ?>
  <?php tagged($v); ?>
  <?php } ?>
  <br class="clbr">
    
  <h2 class="top">その他</h2>
  <?php foreach($view['tags_none'] as $v){ ?>
  <?php tagged($v); ?>
  <?php } ?>
  <br class="clbr">

</div>
<?php require('footer.inc');?>
