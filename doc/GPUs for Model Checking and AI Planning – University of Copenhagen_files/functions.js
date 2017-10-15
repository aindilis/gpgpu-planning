
function addListener(element, eventName, callback) {
	if(element.addEventListener) {
		element.addEventListener(eventName, callback, false);
	}
	else if(element.attachEvent) {
		element.attachEvent("on" + eventName, callback);
	}
	else {
		element[ "on" + eventName ] = callback;
	}
	return callback;
}


/* Overview lists mouse-over for IE function */
startList = function() {
	if( document.all && document.getElementById ) {
		if( document.getElementById("overview") ) {
			navRoot = document.getElementById("overview");
			for (i=0; i<navRoot.childNodes.length; i++) {
				node = navRoot.childNodes[i];
				if (node.nodeName.toLowerCase()=="li") {
					node.onmouseover=function() {
						this.className+=" hover";
					}
					node.onmouseout=function() {
						this.className=this.className.replace(" hover", "");
					}
				}
			}
		}
	}
}



/* Dropdown selectbox functions */
function selectItem(selectedNode){
	/*
	TODO: Check nodes/structure
	*/
	var selectedNodeHref = selectedNode.getAttribute("href");
	var oImg = copyImgNode(selectedNode.childNodes[0]);
	var oTxt = document.createTextNode(selectedNode.childNodes[1].data);
	var targetNode = selectedNode.parentNode.parentNode.parentNode.parentNode;

	//targetNode.childNodes[0].getAttribute("href") = "/";
	//targetNode.childNodes[0].getAttribute("onclick") = "return false";
	/* TODO: Add value to a hidden form field... */

	if(targetNode.childNodes[0].childNodes[0].nodeName=="IMG"){
		targetNode.childNodes[0].removeChild(targetNode.childNodes[0].childNodes[0]);
	}

	targetNode.childNodes[0].childNodes[0].data = oTxt.data;
	targetNode.childNodes[0].insertBefore(oImg, targetNode.childNodes[0].childNodes[0]);
}

function copyImgNode(originalNode){
	var newImageNode = document.createElement("img");
	newImageNode.setAttribute("src", originalNode.getAttribute("src"));
	newImageNode.setAttribute("alt", originalNode.getAttribute("alt"));
	newImageNode.setAttribute("width", originalNode.getAttribute("width"));
	newImageNode.setAttribute("height", originalNode.getAttribute("height"));
	return newImageNode;
}



/* Dreamweaver functions */
function MM_preloadImages() { //v3.0
  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
    if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

function MM_swapImgRestore() { //v3.0
  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
}

function MM_findObj(n, d) { //v4.01
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
  if(!x && d.getElementById) x=d.getElementById(n); return x;
}

function MM_swapImage() { //v3.0
  var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
   if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
}

function MM_jumpMenu(targ,selObj,restore){ //v3.0
  //eval(targ+".location='"+selObj.options[selObj.selectedIndex].value+"'");
  if (restore) selObj.selectedIndex=0;
}


/* Style switcher functions */
function resizeText(){
	var activeCss = getActiveStyleSheet();
	((activeCss=="standard") || (activeCss==null)) ? setActiveStyleSheet("large") : setActiveStyleSheet("standard");
}

var classAttr = /MSIE [2-7]/.test(navigator.userAgent) ? 'className' : "class";

function setActiveStyleSheet(title) {
	var body = document.getElementsByTagName("body")[0];
	var bodyClass = body.getAttribute(classAttr) || '';
	bodyClass = bodyClass.replace(/\s*large\b/, '');
	if(title == 'large')
		bodyClass += " large";
	body.setAttribute(classAttr, bodyClass);
	createCookie("style", title);
}

function getActiveStyleSheet() {
	var bodyClass = document.getElementsByTagName("body")[0].getAttribute(classAttr) || '';
	return bodyClass.indexOf("large") == -1 ? 'standard' : 'large';
}

function createCookie(name,value,days) {
  if (days) {
    var date = new Date();
    date.setTime(date.getTime()+(days*24*60*60*1000));
    var expires = "; expires="+date.toGMTString();
  }
  else expires = "";
  document.cookie = name+"="+value+expires+"; path=/;domain=" + (window.textsize_cookie_domain || '.ku.dk');
  
}

function readCookie(name) {
  var nameEQ = name + "=";
  var ca = document.cookie.split(';');
  for(var i=0;i < ca.length;i++) {
    var c = ca[i];
    while (c.charAt(0)==' ') c = c.substring(1,c.length);
    if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
  }
  return null;
}

function getPreferredStyleSheet() {
	var i, a;
	for(i=0; (a = document.getElementsByTagName("link")[i]); i++) {
	 if(a.getAttribute("rel").indexOf("style") != -1
		 && a.getAttribute("rel").indexOf("alt") == -1
		 && a.getAttribute("title")
		 ) return a.getAttribute("title");
		return null;
	}
}


function add_on_dom_ready(fn) {
    if(document.addEventListener) {   // Mozilla, Opera, Webkit are all happy with this
	document.addEventListener("DOMContentLoaded", function()
	{
	    document.removeEventListener( "DOMContentLoaded", arguments.callee, false);
	    fn();
	}, false);
    }
    else if(document.attachEvent) {   // IE is different...
	document.attachEvent("onreadystatechange", function()
	{
	    if(document.readyState === "complete") {
		document.detachEvent("onreadystatechange", arguments.callee);
		fn();
	    }
	});
    }
}

/*
window.onload = function(e) {
	var cookie = readCookie("style");
	var title = cookie ? cookie : getPreferredStyleSheet();
	setActiveStyleSheet(title);
}
*/
add_on_dom_ready(function() {
    var cookie = readCookie("style");
    var title = cookie || 'standard';
    setActiveStyleSheet(title);
    
    var videresend = document.getElementById('videresendlink'),
        resizetext = document.getElementById('resizetextlink'),
	print = document.getElementById('printlink');

    var preventDefault = function(e) {
	if(e.preventDefault)
	    e.preventDefault();
	else
	    e.returnValue = false;
    }
    if(videresend) {
	addListener(videresend, "click", function(e) {
	    open_videresend();
	    preventDefault(e);
	    return false;
	});
	videresend.setAttribute('onclick', '');
    }
    if(resizetext) {
	addListener(resizetext, "click", function(e) {
	    resizeText();
	    preventDefault(e);
	    return false;
	});
	resizetext.setAttribute('onclick', '');
    }
    if(print) {
	addListener(print, "click", function(e) {
	    window.print();
	    preventDefault(e);
	    return false;
	})
	print.setAttribute('onclick', '');
    }
});

window.onunload = function(e) {
	if(document.getElementsByTagName){
		var title = getActiveStyleSheet();
		createCookie("style", title, 365);
	}
}


/* Add eventlisteners */

//addListener( window, "load", MM_preloadImages('../images/icons/word_over.gif','../images/icons/pdf_over.gif','../images/icons/excel_over.gif') );
addListener( window, "load", startList );



function open_videresend(url) {
    var url = document.location.href;
    window.open("./?videresend=1&url=" + escape(url), "videresend", "width=450,height=530,scrollbars=yes,resizable=yes");
    return false;
}

/* KU mouseover-functions */
function KU_mouseover (obj, src, x, y) {
  if (document.getElementById) {
    o = document.getElementById(obj);
    //o.style.backgroundImage = "url("+src+")";
    o.style.backgroundPosition = x+"px "+y+"px";
  }
}

function KU_mouseout(obj, src, x, y) {
  if (document.getElementById) {
		o = document.getElementById(obj);
		//o.style.backgroundImage = "url("+src+")";
		o.style.backgroundPosition = "0px 0px";
	}
}

function set_cookie(name, value, expires) {
  var cookie = [];
  cookie.push([name,escape(value)]);

  if (!expires) {
    var now = new Date();
    var secs = now.getTime();
    secs += 3600;
    now.setTime(secs);
    expires = now;
  }

  cookie.push(["expires", expires.toGMTString()]);

  var path = document.location.href.replace(/\?.*$/, "").replace(/http:\/\/[^\/]+/, "");
  cookie.push(["path", path]);

  for (var i = 0, len = cookie.length;i < len; i++) {
    cookie[i] = cookie[i].join("=");
  }
  cookie = cookie.join(";");

  document.cookie = cookie;
  return cookie;
}

function delete_search_cookie() {
  set_cookie("obvius_search_cookie", "", new Date(1970,1,1));
}


/* Obtain a url parameter value */
function getUrlParameter( name ) {
    name = name.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");
    var regex = new RegExp( "[\\?&]"+name+"=([^&#]*)" );
    var results = regex.exec( window.location.href );
    if (results == null) {
        return "";
    }
    else {
        return _utf8_decode(unescape(results[1]));
    }
}

function _utf8_decode (utftext) {
    var string = "";
    var i = 0;
    var c = c1 = c2 = 0;

    while ( i < utftext.length ) {

        c = utftext.charCodeAt(i);

        if (c < 128) {
            string += String.fromCharCode(c);
            i++;
        }
        else if((c > 191) && (c < 224)) {
            c2 = utftext.charCodeAt(i+1);
            string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
            i += 2;
        }
        else {
            c2 = utftext.charCodeAt(i+1);
            c3 = utftext.charCodeAt(i+2);
            string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
            i += 3;
        }

    }
    return string;
}
