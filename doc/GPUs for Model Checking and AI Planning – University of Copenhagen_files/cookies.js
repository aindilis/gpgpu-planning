(function() {
    if(document.cookie.match(/accept_cookies\s*=\s*yes/))
        return;

    var cookietest = function() {
	var vdoc_lang = window.vdoc_lang || 'da';
        var div = document.createElement('div');
        div.id = 'cookie_box';
        if ( vdoc_lang == 'da' ) {
            div.innerHTML = '' +
              '<div><h2>Accept af cookies fra ku.dk</h2>' +
              '<p> Ku.dk bruger blandt andet cookies til at udarbejde statistik over anvendelsen af sitet.</p>' +
              '<p>Du kan altid slette cookies fra ku.dk igen.</p>' +
              '<a class="accept_cookies" href="javascript:void(0)" onclick="accept_ku_cookies()">Accepter cookies</a>' +
              '<a class="laes_mere_cookies" href="http://velkommen.ku.dk/om-webstedet/cookie-og-privatlivspolitik/">Læs mere om cookies på ku.dk</a></div>';
        } else {
            div.className = 'english';
            div.innerHTML = '' +
              '<div><h2>Accept of cookies from www.ku.dk</h2>' +
              '<p>The University of Copenhagen uses cookies as part of the statistics work on its website www.ku.dk</p>' +
              '<p>You can erase cookies from www.ku.dk at any time.</p>' +
              '<a class="accept_cookies" href="javascript:void(0)" onclick="accept_ku_cookies()">Accept cookies</a>' +
              '<a class="laes_mere_cookies" href="http://introduction.ku.dk/cookies-and-privacy-policy/">Read more about cookies on www.ku.dk</a></div>';
        }
        var body = document.getElementsByTagName('body')[0];
        body.insertBefore(div, body.firstChild);
    };
    if(document.addEventListener) {   // Mozilla, Opera, Webkit are all happy with this
	document.addEventListener("DOMContentLoaded", function() {
	    document.removeEventListener( "DOMContentLoaded", arguments.callee, false);
	    cookietest();
	}, false);
    }
    else if(document.attachEvent) {   // IE is different...
	document.attachEvent("onreadystatechange", function() {
	    if(document.readyState === "complete") {
		document.detachEvent("onreadystatechange", arguments.callee);
		cookietest();
	    }
	});
    }

})();

function accept_ku_cookies() {
    var div = document.getElementById('cookie_box');
    div.parentNode.removeChild(div);

    // Expire in one year
    var expires = new Date();
    expires.setFullYear(expires.getFullYear() + 1);

    document.cookie = "accept_cookies=yes; " +
        "expires=" + expires.toGMTString() + "; " +
        "path=/";
    return false;
}
