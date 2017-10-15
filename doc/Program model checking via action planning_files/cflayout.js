/*ADOBE SYSTEMS INCORPORATED
Copyright 2007 Adobe Systems Incorporated
All Rights Reserved.

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the
terms of the Adobe license agreement accompanying it.  If you have received this file from a
source other than Adobe, then your use, modification, or distribution of it requires the prior
written permission of Adobe.*/
if(!ColdFusion.Layout){
ColdFusion.Layout={};
}
ColdFusion.Layout.initializeTabLayout=function(id,_2f6){
var _2f7=new Ext.TabPanel(id,_2f6);
ColdFusion.objectCache[id]=_2f7;
return _2f7;
};
ColdFusion.Layout.getTabLayout=function(_2f8){
var _2f9=ColdFusion.objectCache[_2f8];
if(!_2f9||!(_2f9 instanceof Ext.TabPanel)){
ColdFusion.handleError(null,"layout.gettablayout.notfound","widget",[_2f8],null,null,true);
}
return _2f9;
};
ColdFusion.Layout.onTabActivate=function(_2fa,tab){
tab._cf_visible=true;
if(tab._cf_dirtyview){
var _2fc=ColdFusion.bindHandlerCache[tab.id];
if(_2fc){
_2fc();
}
tab._cf_dirtyview=false;
}
var el=Ext.get(tab.id);
el.move("left",1);
el.move("right",1);
};
ColdFusion.Layout.onTabDeactivate=function(_2fe,tab){
tab._cf_visible=false;
if(tab._cf_refreshOnActivate){
tab._cf_dirtyview=true;
}
};
ColdFusion.Layout.onTabClose=function(tab){
tab._cf_visible=false;
};
ColdFusion.Layout.addTab=function(_301,id,_303,_304,_305){
var tab=_301.addTab(id,_303,null,_304);
tab._cf_visible=false;
tab._cf_dirtyview=true;
tab._cf_refreshOnActivate=_305;
tab.addListener("activate",ColdFusion.Layout.onTabActivate);
tab.addListener("deactivate",ColdFusion.Layout.onTabDeactivate);
tab.addListener("close",ColdFusion.Layout.onTabClose);
ColdFusion.objectCache[id]=tab;
};
ColdFusion.Layout.enableTab=function(_307,_308){
var _309=ColdFusion.objectCache[_307];
if(_309&&(_309 instanceof Ext.TabPanel)){
_309.enableTab(_308);
ColdFusion.Log.info("layout.enabletab.enabled","widget",[_308,_307]);
}else{
ColdFusion.handleError(null,"layout.enabletab.notfound","widget",[_307],null,null,true);
}
};
ColdFusion.Layout.disableTab=function(_30a,_30b){
var _30c=ColdFusion.objectCache[_30a];
if(_30c&&(_30c instanceof Ext.TabPanel)){
_30c.disableTab(_30b);
ColdFusion.Log.info("layout.disabletab.disabled","widget",[_30b,_30a]);
}else{
ColdFusion.handleError(null,"layout.disabletab.notfound","widget",[_30a],null,null,true);
}
};
ColdFusion.Layout.selectTab=function(_30d,_30e){
var _30f=ColdFusion.objectCache[_30d];
if(_30f&&(_30f instanceof Ext.TabPanel)){
_30f.activate(_30e);
ColdFusion.Log.info("layout.selecttab.selected","widget",[_30e,_30d]);
}else{
ColdFusion.handleError(null,"layout.selecttab.notfound","widget",[_30d],null,null,true);
}
};
ColdFusion.Layout.hideTab=function(_310,_311){
var _312=ColdFusion.objectCache[_310];
if(_312&&(_312 instanceof Ext.TabPanel)){
var _313=_312.getTab(_311);
var _314=false;
if(_313){
if(_313.isActive()==true){
var i;
for(i=0;i<_312.getCount();i++){
var _316=_312.getTab(i);
if(_316.isHidden()==false){
_314=true;
_316.activate();
break;
}
}
if(_314==false){
document.getElementById(_311).style.display="none";
}
}
_312.hideTab(_311);
ColdFusion.Log.info("layout.hidetab.hide","widget",[_311,_310]);
}
}else{
ColdFusion.handleError(null,"layout.hidetab.notfound","widget",[_310],null,null,true);
}
};
ColdFusion.Layout.showTab=function(_317,_318){
var _319=ColdFusion.objectCache[_317];
if(_319&&(_319 instanceof Ext.TabPanel)){
_319.unhideTab(_318);
document.getElementById(_318).style.display="";
ColdFusion.Log.info("layout.showtab.show","widget",[_318,_317]);
}else{
ColdFusion.handleError(null,"layout.showtab.notfound","widget",[_317],null,null,true);
}
};
ColdFusion.Layout.createTab=function(_31a,_31b,_31c,_31d,_31e){
var _31f=ColdFusion.objectCache[_31a];
if(_31a&&typeof (_31a)!="string"){
ColdFusion.handleError(null,"layout.createtab.invalidname","widget",null,null,null,true);
return;
}
if(!_31a||ColdFusion.trim(_31a)==""){
ColdFusion.handleError(null,"layout.createtab.emptyname","widget",null,null,null,true);
return;
}
if(_31b&&typeof (_31b)!="string"){
ColdFusion.handleError(null,"layout.createtab.invalidareaname","widget",null,null,null,true);
return;
}
if(!_31b||ColdFusion.trim(_31b)==""){
ColdFusion.handleError(null,"layout.createtab.emptyareaname","widget",null,null,null,true);
return;
}
if(_31c&&typeof (_31c)!="string"){
ColdFusion.handleError(null,"layout.createtab.invalidtitle","widget",null,null,null,true);
return;
}
if(!_31c||ColdFusion.trim(_31c)==""){
ColdFusion.handleError(null,"layout.createtab.emptytitle","widget",null,null,null,true);
return;
}
if(_31d&&typeof (_31d)!="string"){
ColdFusion.handleError(null,"layout.createtab.invalidurl","widget",null,null,null,true);
return;
}
if(!_31d||ColdFusion.trim(_31d)==""){
ColdFusion.handleError(null,"layout.createtab.emptyurl","widget",null,null,null,true);
return;
}
if(_31f&&(_31f instanceof Ext.TabPanel)){
var _320=null;
var ele=document.getElementById(_31b);
if(ele!=null){
ColdFusion.handleError(null,"layout.createtab.duplicateel","widget",[_31b],null,null,true);
return;
}
var _322=false;
var _323=false;
var _324=false;
var _325=false;
if((_31f.getCount()<=0)){
_324=true;
}
if(_31e!=null){
if(typeof (_31e)!="object"){
ColdFusion.handleError(null,"layout.createtab.invalidconfig","widget",null,null,null,true);
return;
}
if(typeof (_31e.closable)!="undefined"&&_31e.closable==true){
_322=true;
}
if(typeof (_31e.disabled)!="undefined"&&_31e.disabled==true){
_323=true;
}
if(typeof (_31e.selected)!="undefined"&&_31e.selected==true){
_324=true;
}
if(typeof (_31e.inithide)!="undefined"&&_31e.inithide==true){
_325=true;
}
}
var _326=document.getElementById(_31a);
if(_326){
var _327=document.getElementById(_31a);
var _328=document.createElement("div");
_328.id=_31b;
_328.className="ytab";
if(_31e!=null&&typeof (_31e.align)!="undefined"){
_328.align=_31e.align;
}
var _329="";
if(_31f.tabheight){
_329="height:"+_31f.tabheight+";";
}
if(_31e!=null&&typeof (_31e.style)!="undefined"){
var _32a=new String(_31e.style);
_32a=_32a.toLowerCase();
_329=_329+_32a;
}
if(_31e!=null&&typeof (_31e.overflow)!="undefined"){
var _32b=new String(_31e.overflow);
_32b=_32b.toLowerCase();
if(_32b!="visible"&&_32b!="auto"&&_32b!="scroll"&&_32b!="hidden"){
ColdFusion.handleError(null,"layout.createtab.invalidoverflow","widget",null,null,null,true);
return;
}
_329=_329+"overflow:"+_32b+";";
}else{
_329=_329+"; overflow:auto;";
}
_328.style.cssText=_329;
_327.appendChild(_328);
}
_320=_31f.addTab(_31b,_31c,null,_322);
ColdFusion.Log.info("layout.createtab.success","http",[_31b,_31a]);
if(_324==true){
_31f.activate(_31b);
}
if(_323==true){
ColdFusion.Layout.disableTab(_31a,_31b);
}
if(_325==true){
ColdFusion.Layout.hideTab(_31a,_31b);
}
if(_31d!=null&&typeof (_31d)!="undefined"&&_31d!=""){
if(_31d.indexOf("?")!=-1){
_31d=_31d+"&";
}else{
_31d=_31d+"?";
}
var _32c;
var _32d;
if(_31e){
_32c=_31e.callbackHandler;
_32d=_31e.errorHandler;
}
ColdFusion.Ajax.replaceHTML(_31b,_31d,"GET",null,_32c,_32d);
}
}else{
ColdFusion.handleError(null,"layout.createtab.notfound","widget",[_31a],null,null,true);
}
};
ColdFusion.Layout.getBorderLayout=function(_32e){
var _32f=ColdFusion.objectCache[_32e];
if(!_32f||!(_32f instanceof Ext.BorderLayout)){
ColdFusion.handleError(null,"layout.getborderlayout.notfound","widget",[_32e],null,null,true);
}
return _32f;
};
ColdFusion.Layout.showArea=function(_330,_331){
var _332=ColdFusion.Layout.convertPositionToDirection(_331);
var _333=ColdFusion.objectCache[_330];
if(_333&&(_333 instanceof Ext.BorderLayout)){
var _334=_333.getRegion(_332);
if(_334){
_334.show();
_334.expand();
ColdFusion.Log.info("layout.showarea.shown","widget",[_331,_330]);
}else{
ColdFusion.handleError(null,"layout.showarea.areanotfound","widget",[_331],null,null,true);
}
}else{
ColdFusion.handleError(null,"layout.showarea.notfound","widget",[_330],null,null,true);
}
};
ColdFusion.Layout.hideArea=function(_335,_336){
var _337=ColdFusion.Layout.convertPositionToDirection(_336);
var _338=ColdFusion.objectCache[_335];
if(_338&&(_338 instanceof Ext.BorderLayout)){
var _339=_338.getRegion(_337);
if(_339){
_339.hide();
ColdFusion.Log.info("layout.hidearea.hidden","widget",[_336,_335]);
}else{
ColdFusion.handleError(null,"layout.hidearea.areanotfound","widget",[_336],null,null,true);
}
}else{
ColdFusion.handleError(null,"layout.hidearea.notfound","widget",[_335],null,null,true);
}
};
ColdFusion.Layout.collapseArea=function(_33a,_33b){
var _33c=ColdFusion.Layout.convertPositionToDirection(_33b);
var _33d=ColdFusion.objectCache[_33a];
if(_33d&&(_33d instanceof Ext.BorderLayout)){
var _33e=_33d.getRegion(_33c);
if(_33e){
_33e.collapse(true);
ColdFusion.Log.info("layout.collpasearea.collapsed","widget",[_33b,_33a]);
}else{
ColdFusion.handleError(null,"layout.collpasearea.areanotfound","widget",[_33b],null,null,true);
}
}else{
ColdFusion.handleError(null,"layout.collpasearea.notfound","widget",[_33b],null,null,true);
}
};
ColdFusion.Layout.expandArea=function(_33f,_340){
var _341=ColdFusion.Layout.convertPositionToDirection(_340);
var _342=ColdFusion.objectCache[_33f];
if(_342&&(_342 instanceof Ext.BorderLayout)){
var _343=_342.getRegion(_341);
if(_343){
_343.expand();
ColdFusion.Log.info("layout.expandarea.expanded","widget",[_340,_33f]);
}else{
ColdFusion.handleError(null,"layout.expandarea.areanotfound","widget",[_340],null,null,true);
}
}else{
ColdFusion.handleError(null,"layout.expandarea.notfound","widget",[_340],null,null,true);
}
};
ColdFusion.Layout.convertPositionToDirection=function(_344){
if(_344.toUpperCase()=="LEFT"){
return "west";
}else{
if(_344.toUpperCase()=="RIGHT"){
return "east";
}else{
if(_344.toUpperCase()=="CENTER"){
return "center";
}else{
if(_344.toUpperCase()=="BOTTOM"){
return "south";
}else{
if(_344.toUpperCase()=="TOP"){
return "north";
}
}
}
}
}
};
