<?php require('header.inc');?>

<script>
<!--
    function autoInput(id,s){
    var d = document.getElementById(id);
    d.value = s;
    d.focus();
    }

    $(function(){
    var im = $('#icon');
    var timer = null;
    $('#target').bind('keyup',function(e){
    if(timer != null)clearTimeout(timer);
    timer = setTimeout(function(){
    timer = null;
    var s = e.target.value;
    icon.src= 'http://img.tweetimag.es/i/'+s;
    },250);
    });
    });

-->
</script>

<p>
  <form action="action.php" method="POST">
    タグ<input type="text" name="tag" id="tag" />
    ユーザ名<input type="text" name="target" id="target" />
    <img id="icon">
    <input type="submit" value="タグ付け!" />
    <input type="hidden" name="action" value="link" />
  </form>
</p>

<p>
<?php
foreach($view['data'] as $v){
   if($v[1]>0){
?>
    <div class="tag">
      <a href="?action=tag&tag=<?php echo urlencode($v[0]); ?>"><?php echo esc($v[0]); ?></a>
      <a href="#" onclick="autoInput('tag','<?php echo esc($v[0]); ?>')">■</a>
    </div>
<?php
   }
   }
?>
<br class="clbr" />
</p>

<div class="msg">
  <h3>これは何？</h3>
  Twitterのユーザにタグをつけることができます。
  自分の属性を登録したり、人の属性を登録したりすることで、なんかできんかなと。
  
  ボットで自動巡回してそれっぽいタグをつけるのもやるかもしれない。
  同じ属性を持ってる人を見つけたり、タグのレコメンドとかできると面白いかも。

  とりあえず自分にタグをつけたり、人にタグをつけたりしてみてください
</div>

<div class="msg">
  <h3>タグとして使うと面白そうなもの</h3>
  使えるプログラム言語？、読んだ本？、属しているクラスタ名？、参加したことにあるイベント？、好きな人？、住んでる場所？
</div>

<?php require('footer.inc');?>
