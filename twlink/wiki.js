WikiParser = function(){
    this.cache = [];
    this.ecache = [];
};
WikiParser.prototype = {
    // line mode
    type:{SINGLE:0,LIST:1},
    table:[
	   ["!!!", "h3", 0],
	   ["!!", "h2", 0],
	   ["!", "h1", 0],
	   ["---", "li", 1, 3],
	   ["--", "li", 1, 2],
	   ["-", "li", 1,  1],
	   ["#", "embed", 0],
	   ["%", "embed-u", 0],
	   [">>", "#block", 0]
    ],
    //cache:[],
    //ecache:[],
    parse:function(s,base){
	if(base==undefined){
	    base = document.body;
	}
	function escapeHTML(s){
	    return s.replace(/&/g,'&amp;').replace(/>/g,'&gt;').replace(/</g,'&lt;');
	}
	function escapeHTML2(s){
	    return s.replace(/>/g,'&gt;').replace(/</g,'&lt;');
	}
	function lineF(s){
	    // inline {{----}}
	    var pattern = new RegExp("\{\{([^\}]*?)\}\}","g");
	    var _match;
	    var index = 0;
	    var out = "";
	    var tmp;
	    var cred;
	    while(_match = pattern.exec(s)){
		out += chgUrl(s.substring(index,pattern.lastIndex - _match[0].length));// + "@@" + _match[1] + "@@";
		tmp = _match[1].split(" ");

		out += _match[0];
		index = pattern.lastIndex;
	    }
	    out += chgUrl(s.substring(index,s.length));
	    return out;
	}
	function chgUrl(s){
	    var url = /(http(|s):\/\/[^ ]*)/g;
	    s = escapeHTML(s);
	    s = s.replace(url,function(all){
		    all = escapeHTML2(all);
		    return "<a style='word-break:break-all' href='"+all+"'>"+all+"</a>"
		    +' <a href="http://b.hatena.ne.jp/entry/'+ all +'">'
		    +'<img src="http://b.hatena.ne.jp/entry/image/'+all+'" />'
		    +'</a>';
		})
	    return s;
	}
	var lines = s.split(/[\r\n]/);
	var i,j,k;
	var parsedLines = [];
	var hit;
	var mode = -1;
	var lineBuf = [];
	var tmp;
	var tmp2;
	for(i = 0; i < lines.length; i++){ // lines
	    hit = false;
	    for(j = 0; j < this.table.length; j++){ // table
		if(lines[i].indexOf(this.table[j][0]) == 0){
		    if(mode == 1 && this.table[j][2] == mode){
			// list mode continue
			lineBuf[1].push([this.table[j], lines[i].slice(this.table[j][0].length)]);
		    }else if(this.table[j][2] == 1){
			// first list mode
			lineBuf = [1, [[this.table[j], lines[i].slice(this.table[j][0].length)]]];
			parsedLines.push(lineBuf); // tagged
		    }else{
			if(this.table[j][1] == "#block"){
			    tmp2 = lines[i].replace(/^>>/,'');
			    tmp = [0, ["","pre",0], ""];
			    if(tmp2 == 'quote'){
				tmp = [0, ["","blockquote",0], ""];
			    }else if(tmp2=='mce3'){
				tmp = [0, ["","mce",0], ""];
			    }
			    i++;
			    for(; i < lines.length; i++){
				if(lines[i].indexOf("<<")==0)break;
				tmp[2] += lines[i] + "\n";
			    }
			    parsedLines.push(tmp);
			}else{
			    parsedLines.push([0, this.table[j], lines[i].slice(this.table[j][0].length)]); // tagged
			}
		    }
		    
		    mode = this.table[j][2];
		    hit = true;
		    break;
		}
	    }
	    if(hit == false){
		parsedLines.push([0, ['','',0], lines[i]]); // normal line
		mode = -1;
	    }
	}
	delete lines;
	// parse complete

	
	//console.log(parsedLines);
	var text;
	var tag;
	var level;
	var elm,te,te2;
	var l;
	//var base = document.createElement('div');
	//console.log(base);
	/*
	var fMulti = function(l,e){
	    var li;
	    var te;
	    for(var i = 0; i < l.length; i++){
		if(l[i] instanceof Array){
		    // in
		    te = document.createElement('ul');
		    e.appendChild(te);
		    fMulti(l[i],te);
		    
		}else{
		    li = document.createElement('li');
		    // todo: escapeHTML
		    li.innerHTML = l[i];
		    e.appendChild(li);
		}
	    }
	}
	*/
	var eq = function(a,b){
	    if(a instanceof Array && b instanceof Array){
		if(a.length != b.length)return false;
		for(var i = 0; i < a.length; i++){
		    if(eq(a[i],b[i]) == false)return false;
		}
	    }else if(a==b){
		return true;
	    }else{
		return false;
	    }
	    return true;
	}

	// [0 or 1,string]  formatted?,endtag
	for(i = 0; i < parsedLines.length; i++){
	    var item = parsedLines[i];
	    if(item[0] == 0){
		// single
		// this.cache[i] ~= lineParser[i] ? continue
		if(eq(this.cache[i],item)){
		    continue;
		}

		te2 = this.ecache[i];//document.getElementById("wiki" + i);
		elm = document.createElement('div');
		//console.log(te2);
		if(te2){
		    te2.parentNode.replaceChild(elm, te2);
		}else{
		    base.appendChild(elm);
		}
		this.ecache[i] = elm;
		tag = item[1][1];
		if(tag==""){
		    // not tag
		    if(item[2] == ""){
			elm.innerHTML = '<br/>';
		    }else{
			elm.innerHTML = lineF(item[2]);
		    }
		}else if(tag=="mce"){
		    te2 = document.createElement("div");
		    te2.className = "embedmce3";
		    te2.style.border="solid";
		    te2.mce = item[2]
		    elm.appendChild(te2);
		}else{
		    // create tag
		    te2 = document.createElement(tag);
		    if(tag=="pre"){
			te2.innerHTML = item[2];
		    }if(tag=="h1"){
			$(te2).css('clear','both');
			te2.innerHTML = lineF(item[2]);
		    }else{
			te2.innerHTML = lineF(item[2]);
		    }
		    elm.appendChild(te2);
		}
		//console.log(item[1][1] + ' ' + item[2]);
	    }else if(item[0] == 1){
		//multi
		// this.cache[i] ~= lineParser[i] ? continue
		if(eq(this.cache[i],item)){
		    continue;
		}

		level = 0;
		te2 = this.ecache[i];//document.getElementById("wiki" + i);
		elm = document.createElement('div');
		if(te2){
		    te2.parentNode.replaceChild(elm, te2);
		}else{
		    base.appendChild(elm);
		}
		this.ecache[i] = elm;
		
		te = [elm];
		//fMulti(item[1], elm);
		
		for(j = 0; j < item[1].length; j++){
		    //0-symbol 1-tag 2-signle/multi 3-label
		    text = item[1][j][1];
		    l = item[1][j][0][3];
		    //console.log(item[1][j][0][1] + ' ' + item[1][j][0][3] + ' ' + text);
		    //console.log("level:" + level + ' l:' + l);
		    if(level < l){ // in
			te2 = document.createElement("ul");
			te[te.length - 1].appendChild(te2);
			te.push(te2);
			te2 = document.createElement("li");
			te2.innerHTML = lineF(text);
			te[te.length - 1].appendChild(te2);
		    }else if(level == l){
			te2 = document.createElement("li");
			te2.innerHTML = lineF(text);
			te[te.length - 1].appendChild(te2);
		    }else{ // level > l
			te2 = level - l;
			for(k = 0; k < te2; k++){
			    te.pop();
			}
			te2 = document.createElement("li");
			te2.innerHTML = lineF(text);
			te[te.length - 1].appendChild(te2);
		    }
		    level = l;
		}
		//console.log(te);
	    }
	}

	if(this.cache.length >= i){
	    for(j = this.cache.length - 1; j >= i ; j--){
		//console.log(this.ecache[j])
		te2 = this.ecache[j].parentNode;
		te2.removeChild(this.ecache[j]);
		this.ecache[j] = null;
	    }
	}
	this.cache = parsedLines;
	//document.body.appendChild(base);
    }
}