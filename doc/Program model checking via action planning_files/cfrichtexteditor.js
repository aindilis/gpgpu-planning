/*ADOBE SYSTEMS INCORPORATED
Copyright 2007 Adobe Systems Incorporated
All Rights Reserved.

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the
terms of the Adobe license agreement accompanying it.  If you have received this file from a
source other than Adobe, then your use, modification, or distribution of it requires the prior
written permission of Adobe.*/
if(!ColdFusion.RichText){
ColdFusion.RichText={};
}
ColdFusion.RichText.editorState={};
ColdFusion.RichText.buffer=null;
ColdFusion.RichText.initialize=function(id,name,_350,_351,_352,_353,_354,_355,_356,skin,_358,_359,_35a,_35b,_35c){
var _35d=new FCKeditor(id);
ColdFusion.RichText.editorState[id]=false;
_35d.Value=_350;
_35d.richtextid=id;
if(_351!=null){
_35d.BasePath=_351;
}
if(_352!=null){
_35d.Width=_352;
}
if(_353!=null){
_35d.Height=_353;
}
if(_354!=null){
_35d.Config.FontNames=_354;
}
if(_355!=null){
_35d.Config.FontSizes=_355;
}
if(_356!=null){
_35d.Config.FontFormats=_356;
}
if(skin!=null){
var _35e=_35d.BasePath+"editor/skins/"+skin+"/";
_35d.Config.SkinPath=_35e;
}
if(_358==true){
_35d.Config.ToolbarStartExpanded=false;
_35d.Config.Toolbaronfocus=true;
}
if(_359!=null){
_35d.ToolbarSet=_359;
}
if(_35a!=null){
_35d.Config.StylesXmlPath=_35a;
}
if(_35b!=null){
_35d.Config.TemplatesXmlPath=_35b;
}
_35d.Config.AutoDetectLanguage=false;
if(_35c!=null){
_35d.Config.DefaultLanguage=_35c;
}
_35d.ReplaceTextarea();
var _35f=function(_360){
ColdFusion.RichText.setValue(id,_360);
};
_35d._cf_setValue=_35f;
var _361=function(){
if(ColdFusion.RichText.editorState[id]){
var _362=FCKeditorAPI.GetInstance(id);
return _362.GetXHTML();
}else{
ColdFusion.Log.error("richtext.initialize.getvalue.notready","widget",[id]);
return null;
}
};
_35d._cf_getAttribute=_361;
var _363=function(_364,_365,_366){
var _367=document.getElementById(id);
if(_367){
ColdFusion.Event.addListener(_367,_364,_365,_366);
}
};
_35d._cf_register=_363;
_35d._cf_name=name;
ColdFusion.objectCache[name]=_35d;
ColdFusion.objectCache[id]=_35d;
ColdFusion.RichText.registerAfterSet(id);
ColdFusion.Log.info("richtext.initialize.success","widget",[name]);
};
ColdFusion.RichText.editor_onfocus=function(_368){
_368.ToolbarSet.Expand();
};
ColdFusion.RichText.editor_onblur=function(_369){
_369.ToolbarSet.Collapse();
};
ColdFusion.RichText.setChangeBuffer=function(_36a){
ColdFusion.RichText.buffer=FCKeditorAPI.GetInstance(_36a.Name).GetXHTML();
};
ColdFusion.RichText.resetChangeBuffer=function(_36b){
if(ColdFusion.RichText.buffer!=FCKeditorAPI.GetInstance(_36b.Name).GetXHTML()){
ColdFusion.RichText.fireChangeEvent(_36b.Name);
}
ColdFusion.RichText.buffer=null;
};
ColdFusion.RichText.registerAfterSet=function(_36c){
if(ColdFusion.RichText.editorState[_36c]){
var _36d=function(){
ColdFusion.RichText.fireChangeEvent(_36c);
};
var _36e=FCKeditorAPI.GetInstance(_36c);
_36e.Events.AttachEvent("OnAfterSetHTML",_36d);
}else{
setTimeout("ColdFusion.RichText.registerAfterSet('"+_36c+"')",1000);
}
};
ColdFusion.RichText.getEditorObject=function(_36f){
if(!_36f){
ColdFusion.handleError(null,"richtext.geteditorobject.missingtextareaname","widget",null,null,null,true);
return;
}
var _370=ColdFusion.objectCache[_36f];
if(_370==null||FCKeditor.prototype.isPrototypeOf(_370)==false){
ColdFusion.handleError(null,"richtext.geteditorobject.notfound","widget",[_36f],null,null,true);
return;
}
return FCKeditorAPI.GetInstance(_370.richtextid);
};
ColdFusion.RichText.setValue=function(_371,_372){
if(ColdFusion.RichText.editorState[_371]){
var _373=FCKeditorAPI.GetInstance(_371);
_373.SetHTML(_372);
}else{
setTimeout("ColdFusion.RichText.setValue(\""+_371+"\",\""+_372+"\")",1000);
}
};
ColdFusion.RichText.fireChangeEvent=function(_374){
var _375=ColdFusion.objectCache[_374];
ColdFusion.Log.info("richtext.firechangeevent.firechange","widget",[_375._cf_name]);
ColdFusion.Event.callBindHandlers(_374,null,"change");
};
function FCKeditor_OnComplete(_376){
if(_376.Config.Toolbaronfocus){
_376.Events.AttachEvent("OnBlur",ColdFusion.RichText.editor_onblur);
_376.Events.AttachEvent("OnFocus",ColdFusion.RichText.editor_onfocus);
}
_376.Events.AttachEvent("OnFocus",ColdFusion.RichText.setChangeBuffer);
_376.Events.AttachEvent("OnBlur",ColdFusion.RichText.resetChangeBuffer);
ColdFusion.RichText.editorState[_376.Name]=true;
if(ColdFusion.RichText.OnComplete){
ColdFusion.RichText.OnComplete(_376);
}
}
