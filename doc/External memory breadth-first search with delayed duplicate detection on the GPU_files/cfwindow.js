/*ADOBE SYSTEMS INCORPORATED
Copyright 2007 Adobe Systems Incorporated
All Rights Reserved.

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the
terms of the Adobe license agreement accompanying it.  If you have received this file from a
source other than Adobe, then your use, modification, or distribution of it requires the prior
written permission of Adobe.*/
if(!ColdFusion.Window){
ColdFusion.Window={};
}
ColdFusion.Window.windowIdCounter=1;
ColdFusion.Window.create=function(_1fb,_1fc,url,_1fe){
if(_1fb==null){
ColdFusion.handleError(null,"window.create.nullname","widget",null,null,null,true);
return;
}
if(_1fb==""){
ColdFusion.handleError(null,"window.create.emptyname","widget",null,null,null,true);
return;
}
var _1ff=ColdFusion.objectCache[_1fb];
var _200=false;
if(typeof (_1ff)!="undefined"&&_1ff!=null){
if(_1ff.callfromtag){
ColdFusion.handleError(null,"window.create.duplicatename","widget",[_1fb]);
}
if(typeof (_1ff.isConfObj)!="undefined"&&_1ff.isConfObj==true){
_200=true;
if(_1fe!=null&&typeof (_1fe.initshow)!="undefined"){
if(_1fe.initshow==false){
return;
}
}
}else{
if(!_1fe||(_1fe&&_1fe.initshow!==false)){
ColdFusion.Window.show(_1fb);
}
return;
}
}
if(!_1ff){
ColdFusion.Log.info("window.create.creating","widget",[_1fb]);
}
var _201=ColdFusion.Window.createHTML(_1fb,_1fc,url,_1fe,_200);
var _202=ColdFusion.objectCache[_1fb];
if(_202!=null&&typeof (_202.isConfObj)!="undefined"&&_202.isConfObj==true){
return;
}
ColdFusion.Window.createJSObj(_1fb,url,_201);
};
ColdFusion.Window.createHTML=function(_203,_204,url,_206,_207){
var _208=null;
var _209=null;
if(_206&&_206.divid){
_208=document.getElementById(_206.divid);
}
if(_208==null){
_208=document.createElement("div");
_209="cf_window"+ColdFusion.Window.windowIdCounter;
ColdFusion.Window.windowIdCounter++;
_208.id=_209;
_208.className="yuiextdlg";
}
document.body.appendChild(_208);
var _20a=false;
if(_206!=null&&typeof (_206.headerstyle)!="undefined"&&_206.headerstyle!=null){
var _20b=new String(_206.headerstyle);
_20b=_20b.toLowerCase();
if(_20b.indexOf("background-color")>=0){
_20a=true;
}
}
var _20c=document.getElementById(_203+"_title");
if(_20a==true){
var _20d=document.getElementById(_203+"_b");
if(!_20d){
_20d=document.createElement("b");
_20d.className="corner";
_20d.id=_203+"_b";
for(var i=1;i<4;i++){
var eleb=document.createElement("b");
eleb.className="filler"+i;
eleb.style.cssText=_206.headerstyle;
_20d.appendChild(eleb);
}
if(_20c!=null){
_208.insertBefore(_20d,_20c);
}else{
_208.appendChild(_20d);
}
}
}
if(_20c==null){
_20c=document.createElement("div");
_20c.id=_203+"_title";
var _210="x-dlg-hd";
_20c.className=_210;
if(_204){
_20c.innerHTML=_204;
}else{
_20c.innerHTML="&nbsp;";
}
_208.appendChild(_20c);
}
var _211=document.getElementById(_203+"_body");
if(_211==null){
_211=document.createElement("div");
_211.id=_203+"_body";
_211.className="x-dlg-bd";
_208.appendChild(_211);
}
var _212;
_212=ColdFusion.Window.getUpdatedConfigObj(_206,_203);
if(typeof (_212)=="undefined"){
_208.innerHTML="";
return;
}
if(_209){
_212.divid=_209;
}
if(typeof (_212.initshow)!="undefined"&&_212.initshow===false){
_212.url=url;
ColdFusion.objectCache[_203]=_212;
ColdFusion.objectCache[_203+"_body"]=_212;
}
return _212;
};
ColdFusion.Window.createJSObj=function(_213,url,_215){
var _216;
var _217=false;
if(typeof (_215.childlayoutid)&&_215.childlayoutid!=null){
_217=true;
_216=new Ext.LayoutDialog(_215.divid,_215);
}else{
_216=new Ext.BasicDialog(_215.divid,_215);
}
_216.cfwindowname=_213;
_216.tempx=_215.tempx;
_216.tempy=_215.tempy;
_216.divid=_215.divid;
if(typeof (_215.onShow)!="undefined"){
_216.onShow=_215.onShow;
_216.addListener("show",ColdFusion.Window.onShowWrapper);
}
if(typeof (_215.onHide)!="undefined"){
_216.onHide=_215.onHide;
_216.addListener("hide",ColdFusion.Window.onHideWrapper);
}
if(typeof (_215.headerstyle)!="undefined"&&_215.headerstyle!=null){
var _218=document.getElementById(_213+"_title");
if(_218!=null){
_218.style.cssText="background:none;"+_215.headerstyle;
}
}
if(typeof (_215.bodystyle)!="undefined"&&_215.bodystyle!=null){
var _219=document.getElementById(_213+"_body");
var _21a=_219.parentNode;
if(_21a!=null){
_21a.style.cssText=_215.bodystyle;
}
}
_216.isConfObj=false;
_216._cf_body=_213+"_body";
ColdFusion.objectCache[_213]=_216;
if(_217){
var _21b=_216.getLayout();
var _21c=ColdFusion.objectCache[_215.childlayoutid];
_21b.add("center",new Ext.NestedLayoutPanel(_21c));
}
var _21d=null;
if(typeof (url)!="undefined"&&url!=""){
_21d=url;
}
if(_21d==null){
if(typeof (_215.initshow)=="undefined"||_215.initshow==true){
ColdFusion.Window.showandhide(_216,_215);
}
return;
}
ColdFusion.objectCache[_213+"_body"]=_216;
if(typeof (_215.callfromtag)=="undefined"){
var _21e;
var _21f;
_216._cf_visible=false;
_216._cf_dirtyview=true;
_216.addListener("show",ColdFusion.Window.showHandler);
_216.addListener("hide",ColdFusion.Window.hideHandler);
_216.url=_21d;
if(_215){
if(typeof (_215.initshow)=="undefined"||_215.initshow==true){
ColdFusion.Window.showandhide(_216,_215);
}
_21e=_215.callbackHandler;
_21f=_215.errorHandler;
}
}else{
_216.callfromtag=true;
_216._cf_visible=false;
_216._cf_dirtyview=true;
_216.addListener("show",ColdFusion.Window.showHandler);
_216.addListener("hide",ColdFusion.Window.hideHandler);
if(typeof (_215.initshow)=="undefined"||_215.initshow==true){
ColdFusion.Window.showandhide(_216,_215);
}
}
};
ColdFusion.Window.showandhide=function(_220,_221){
if(typeof (_221.tempinitshow)!="undefined"&&_221.tempinitshow==false){
_220.el.show();
_220.el.hide();
}else{
_220.show();
}
};
ColdFusion.Window.destroy=function(_222,_223){
if(_222){
var _224=ColdFusion.Window.getWindowObject(_222);
if(_224){
if(_223===true){
_224.destroy(true);
}else{
_224.destroy();
}
ColdFusion.objectCache[_222]=null;
}
}
};
ColdFusion.Window.showHandler=function(_225){
_225._cf_visible=true;
if(_225._cf_dirtyview){
if(typeof (_225.callfromtag)=="undefined"){
ColdFusion.Ajax.replaceHTML(_225._cf_body,_225.url,"GET",null,_225.callbackHandler,_225.errorHandler);
}else{
var _226=ColdFusion.bindHandlerCache[_225._cf_body];
if(_226){
_226();
}
}
_225._cf_dirtyview=false;
}
};
ColdFusion.Window.hideHandler=function(_227){
_227._cf_visible=false;
if(_227._cf_refreshOnShow){
_227._cf_dirtyview=true;
}
};
ColdFusion.Window.xPosition=50;
ColdFusion.Window.yPosition=50;
ColdFusion.Window.resetHTML=function(_228){
var _229=document.getElementById(_228);
if(_229){
_229.innerHTML="";
}
};
ColdFusion.Window.getUpdatedConfigObj=function(_22a,_22b){
var _22c={};
if(_22a!=null){
if(typeof (_22a)!="object"){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidconfig","widget",[_22b],null,null,true);
return;
}
for(var key in _22a){
if(key=="center"&&ColdFusion.Util.isBoolean(_22a["center"])){
_22c["fixedcenter"]=_22a["center"];
}else{
_22c[key]=_22a[key];
}
}
}
if(typeof (_22c.initshow)!="undefined"){
if(ColdFusion.Util.isBoolean(_22c.initshow)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidinitshow","widget",[_22b],null,null,true);
return;
}else{
_22c.initshow=ColdFusion.Util.castBoolean(_22c.initshow);
_22c._cf_visible=_22c.initshow;
}
}
_22c.tempcenter=null;
if(typeof (_22c.fixedcenter)!="undefined"){
if(ColdFusion.Util.isBoolean(_22c.fixedcenter)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidcenter","widget",[_22b],null,null,true);
return;
}else{
_22c.fixedcenter=ColdFusion.Util.castBoolean(_22c.fixedcenter);
}
}
if(typeof (_22c.resizable)!="undefined"){
if(ColdFusion.Util.isBoolean(_22c.resizable)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidresizable","widget",[_22b],null,null,true);
return;
}else{
_22c.resizable=ColdFusion.Util.castBoolean(_22c.resizable);
}
}
if(typeof (_22c.draggable)!="undefined"){
if(ColdFusion.Util.isBoolean(_22c.draggable)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invaliddraggable","widget",[_22b],null,null,true);
return;
}else{
_22c.draggable=ColdFusion.Util.castBoolean(_22c.draggable);
}
}
if(typeof (_22c.closable)!="undefined"){
if(ColdFusion.Util.isBoolean(_22c.closable)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidclosable","widget",[_22b],null,null,true);
return;
}else{
_22c.closable=ColdFusion.Util.castBoolean(_22c.closable);
}
}
if(typeof (_22c.modal)!="undefined"){
if(ColdFusion.Util.isBoolean(_22c.modal)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidmodal","widget",[_22b],null,null,true);
return;
}else{
_22c.modal=ColdFusion.Util.castBoolean(_22c.modal);
}
}
if(typeof (_22c.refreshonshow)!="undefined"){
if(ColdFusion.Util.isBoolean(_22c.refreshonshow)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidrefreshonshow","widget",[_22b],null,null,true);
return;
}else{
_22c._cf_refreshOnShow=ColdFusion.Util.castBoolean(_22c.refreshonshow);
}
}
_22c.shadow=true;
if(!_22c.height){
_22c.height=300;
}else{
if(ColdFusion.Util.isInteger(_22c.height)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidheight","widget",[_22b],null,null,true);
return;
}
}
if(!_22c.width){
_22c.width=500;
}else{
if(ColdFusion.Util.isInteger(_22c.width)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidwidth","widget",[_22b],null,null,true);
return;
}
}
var _22e=false;
if(_22c.minwidth){
if(ColdFusion.Util.isInteger(_22c.minwidth)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidminwidth","widget",[_22b],null,null,true);
return;
}
var _22f=_22c.minwidth;
var _230=_22c.width;
if(typeof (_22f)!="number"){
_22f=parseInt(_22f);
}
if(typeof (_230)!="number"){
_230=parseInt(_230);
}
if(_22f>_230){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidminwidth","widget",[_22b],null,null,true);
return;
}
_22c.minWidth=_22c.minwidth;
_22e=true;
}
if(_22c.minheight){
if(ColdFusion.Util.isInteger(_22c.minheight)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidminheight","widget",[_22b],null,null,true);
return;
}
var _231=_22c.minheight;
var _232=_22c.height;
if(typeof (_231)!="number"){
_231=parseInt(_231);
}
if(typeof (_232)!="number"){
_232=parseInt(_232);
}
if(_231>_232){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidheightvalue","widget",[_22b],null,null,true);
return;
}
_22c.minHeight=_22c.minheight;
_22e=true;
}
if(_22c.x){
if(ColdFusion.Util.isInteger(_22c.x)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidx","widget",[_22b],null,null,true);
return;
}
}
if(_22c.y){
if(ColdFusion.Util.isInteger(_22c.y)==false){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.invalidy","widget",[_22b],null,null,true);
return;
}
}
if(typeof (_22c.x)=="undefined"&&(typeof (_22c.center)=="undefined"||_22c.center==false)){
_22c.x=ColdFusion.Window.xPosition;
ColdFusion.Window.xPosition+=15;
}
if(typeof (_22c.y)=="undefined"&&(typeof (_22c.center)=="undefined"||_22c.center==false)){
_22c.y=ColdFusion.Window.yPosition;
ColdFusion.Window.yPosition+=15;
}
if(typeof (_22c.initshow)!="undefined"&&_22c.initshow===false){
_22c.tempinitshow=false;
if(typeof (_22c.fixedcenter)!="undefined"&&_22c.fixedcenter===true){
_22c.tempcenter=_22c.fixedcenter;
_22c.fixedcenter=null;
}else{
_22c.tempx=_22c.x;
_22c.tempy=_22c.y;
}
_22c.x=-10000;
_22c.y=-10000;
}
_22c.constraintoviewport=true;
_22c.initshow=true;
if(_22c.resizable!=null&&_22c.resizable==false&&_22e==true){
ColdFusion.Window.resetHTML(_22b);
ColdFusion.handleError(null,"window.getupdatedconfigobject.minhwnotallowed","widget",[_22b],null,null,true);
return;
}
_22c.collapsible=false;
_22c.shadow=true;
_22c.isConfObj=true;
return _22c;
};
ColdFusion.Window.show=function(_233){
var _234=ColdFusion.objectCache[_233];
if(typeof (_234)!="undefined"&&_234!=null){
if(typeof (_234.isConfObj)!="undefined"&&_234.isConfObj==true){
_234.initshow=true;
var _235=ColdFusion.Window.createHTML(_233,null,_234.url,_234,true);
ColdFusion.Window.createJSObj(_233,_234.url,_235);
}else{
if(_234.isVisible()==false){
_234.show();
ColdFusion.Log.info("window.show.shown","widget",[_233]);
}
if(_234.tempcenter!=null){
_234.center();
_234.tempcenter=null;
}else{
if(_234.getEl()&&_234.getEl().getX()>0&&_234.getEl().getY()>0){
_234.tempx=null;
_234.tempy=null;
}else{
if(_234.tempx!=null&&_234.tempy!=null){
_234.moveTo(_234.tempx,_234.tempy);
_234.tempx=null;
_234.tempy=null;
}else{
var x=_234.getEl().getX();
var y=_234.getEl().getY();
_234.moveTo(x+1,y+1);
_234.moveTo(x,y);
}
}
}
Ext.DialogManager.bringToFront(_234);
}
}else{
ColdFusion.handleError(null,"window.show.notfound","widget",[_233],null,null,true);
}
};
ColdFusion.Window.hide=function(_238){
var _239=ColdFusion.objectCache[_238];
if(_239){
if(_239.isVisible&&_239.isVisible()==true){
_239.hide();
ColdFusion.Log.info("window.hide.hidden","widget",[_238]);
}
}else{
ColdFusion.handleError(null,"window.hide.notfound","widget",[_238],null,null,true);
}
};
ColdFusion.Window.onShow=function(_23a,_23b){
var _23c=ColdFusion.objectCache[_23a];
if(typeof (_23c)!="undefined"&&_23c!=null){
_23c.onShow=_23b;
if(_23c.addListener){
_23c.addListener("show",ColdFusion.Window.onShowWrapper);
}
}else{
ColdFusion.handleError(null,"window.onshow.notfound","widget",[_23a],null,null,true);
}
};
ColdFusion.Window.onShowWrapper=function(_23d){
_23d.onShow.call(null,_23d.cfwindowname);
};
ColdFusion.Window.onHide=function(_23e,_23f){
var _240=ColdFusion.objectCache[_23e];
if(typeof (_240)!="undefined"&&_240!=null){
_240.onHide=_23f;
if(_240.addListener){
_240.addListener("hide",ColdFusion.Window.onHideWrapper);
}
}else{
ColdFusion.handleError(null,"window.onhide.notfound","widget",[_23e],null,null,true);
}
};
ColdFusion.Window.onHideWrapper=function(_241){
_241.onHide.call(null,_241.cfwindowname);
};
ColdFusion.Window.getWindowObject=function(_242){
if(!_242){
ColdFusion.handleError(null,"window.getwindowobject.emptyname","widget",null,null,null,true);
return;
}
var _243=ColdFusion.objectCache[_242];
if(_243==null||(typeof (_243.isConfObj)=="undefined"&&Ext.LayoutDialog.prototype.isPrototypeOf(_243)==false&&Ext.BasicDialog.prototype.isPrototypeOf(_243)==false)){
ColdFusion.handleError(null,"window.getwindowobject.notfound","widget",[_242],null,null,true);
return;
}
if(typeof (_243.isConfObj)!="undefined"&&_243.isConfObj==true){
_243.initshow=true;
var _244=ColdFusion.Window.createHTML(_242,null,_243.url,_243,true);
ColdFusion.Window.createJSObj(_242,_243.url,_244);
ColdFusion.Window.hide(_242);
_243=ColdFusion.objectCache[_242];
}
return _243;
};
