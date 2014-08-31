

/* TABLE Flags */
DROP TABLE IF EXISTS "Flags";
CREATE TABLE "Flags" 
(	"Type" TEXT NOT NULL
,	"Mask" TEXT NOT NULL
,	"Name" TEXT NOT NULL
,	"Description" TEXT NOT NULL
);

/* PropertyType */
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000000",	"PropertyTypeNone",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000001",	"PropertyTypeByte",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000002",	"PropertyTypeInt",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000003",	"PropertyTypeBool",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000004",	"PropertyTypeFloat",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000005",	"PropertyTypeObject",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000006",	"PropertyTypeName",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000007",	"PropertyTypeString",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000008",	"PropertyTypeClass",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x00000009",	"PropertyTypeArray",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x0000000a",	"PropertyTypeStruct",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x0000000b",	"PropertyTypeVector",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x0000000c",	"PropertyTypeRotator",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x0000000d",	"PropertyTypeStr",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x0000000e",	"PropertyTypeMap",	"");
INSERT INTO "Flags" VALUES("PropertyType",	"0x0000000f",	"PropertyTypeFixedArray",	"");

/* FileMarkers */
INSERT INTO "Flags" VALUES("FileMarkers",	"0x00000000",	"None",				"Undefined");
INSERT INTO "Flags" VALUES("FileMarkers",	"0x00000001",	"Header",			"Package header");
INSERT INTO "Flags" VALUES("FileMarkers",	"0x00000002",	"NameTable",		"Name table");
INSERT INTO "Flags" VALUES("FileMarkers",	"0x00000004",	"ImportTable",		"Import table");
INSERT INTO "Flags" VALUES("FileMarkers",	"0x00000008",	"ExportTable",		"Export table");
INSERT INTO "Flags" VALUES("FileMarkers",	"0x00000010",	"GenerationTable",	"Generation table");
INSERT INTO "Flags" VALUES("FileMarkers",	"0x00000020",	"Object",			"Serialized object");


/* Function */
INSERT INTO "Flags" VALUES("Function",	"0x00000001",	"Final",	"Function is final (prebindable, non-overridable function).");
INSERT INTO "Flags" VALUES("Function",	"0x00000002",	"Defined",	"Function has been defined (not just declared).");
INSERT INTO "Flags" VALUES("Function",	"0x00000004",	"Iterator",	"Function is an iterator.");
INSERT INTO "Flags" VALUES("Function",	"0x00000008",	"Latent",	"Function is a latent state function.");
INSERT INTO "Flags" VALUES("Function",	"0x00000010",	"PreOperator",	"Unary operator is a prefix operator.");
INSERT INTO "Flags" VALUES("Function",	"0x00000020",	"Singular",	"Function cannot be reentered.");
INSERT INTO "Flags" VALUES("Function",	"0x00000040",	"Net",	"Function is network-replicated.");
INSERT INTO "Flags" VALUES("Function",	"0x00000080",	"NetReliable",	"Function should be sent reliably on the network.");
INSERT INTO "Flags" VALUES("Function",	"0x00000100",	"Simulated",	"Function executed on the client side.");
INSERT INTO "Flags" VALUES("Function",	"0x00000200",	"Exec",	"Executable from command line.");
INSERT INTO "Flags" VALUES("Function",	"0x00000400",	"Native",	"Native function.");
INSERT INTO "Flags" VALUES("Function",	"0x00000800",	"Event",	"Event function.");
INSERT INTO "Flags" VALUES("Function",	"0x00001000",	"Operator",	"Operator function.");
INSERT INTO "Flags" VALUES("Function",	"0x00002000",	"Static",	"Static function.");
INSERT INTO "Flags" VALUES("Function",	"0x00004000",	"NoExport",	"Don't export intrinsic function to C++.");
INSERT INTO "Flags" VALUES("Function",	"0x00008000",	"Const",	"Function doesn't modify this object.");
INSERT INTO "Flags" VALUES("Function",	"0x00010000",	"Invariant",	"Return value is purely dependent on parameters; no state dependencies or internal state changes");
INSERT INTO "Flags" VALUES("Function",	"0x00020000",	"Public",	"Can be accessed from all classes.");
INSERT INTO "Flags" VALUES("Function",	"0x00040000",	"Private",	"Can be accessed only from the class it's in; no other classes (including subclasses) may access it.");
INSERT INTO "Flags" VALUES("Function",	"0x00080000",	"Protected",	"Can be accessed from the class and it's subclasses, not from other classes.");
INSERT INTO "Flags" VALUES("Function",	"0x00100000",	"Delegate",	"Function is a delegate.");	

/* State */
INSERT INTO "Flags" VALUES("State",	"0x00000001",	"Editable",	"State should be user-selectable in UnrealEd.");
INSERT INTO "Flags" VALUES("State",	"0x00000002",	"Auto",	"State is automatic (the default state).");
INSERT INTO "Flags" VALUES("State",	"0x00000004",	"Simulated",	"State executes on client side.");		

/* Load */
INSERT INTO "Flags" VALUES("Load",	"0x00000000",	"Propagate",	"");
INSERT INTO "Flags" VALUES("Load",	"0x00000000",	"None",	"No flags.");
INSERT INTO "Flags" VALUES("Load",	"0x00000001",	"NoFail",	"Critical error if load fails.");
INSERT INTO "Flags" VALUES("Load",	"0x00000002",	"NoWarn",	"Don't display warning if load fails.");
INSERT INTO "Flags" VALUES("Load",	"0x00000008",	"Throw",	"Throw exceptions upon failure.");
INSERT INTO "Flags" VALUES("Load",	"0x00000010",	"Verify",	"Only verify existance; don't actually load.");
INSERT INTO "Flags" VALUES("Load",	"0x00000020",	"AllowDll",	"Allow plain DLLs.");
INSERT INTO "Flags" VALUES("Load",	"0x00000040",	"DisallowFiles",	"Don't load from file.");
INSERT INTO "Flags" VALUES("Load",	"0x00000080",	"NoVerify",	"Don't verify imports yet.");
INSERT INTO "Flags" VALUES("Load",	"0x00001000",	"Forgiving",	"Forgive missing imports (set them to NULL).");
INSERT INTO "Flags" VALUES("Load",	"0x00002000",	"Quiet",	"No log warnings.");
INSERT INTO "Flags" VALUES("Load",	"0x00004000",	"NoRemap",	"No remapping of packages.");		

/* Package */
INSERT INTO "Flags" VALUES("Package",	"0x00000001",	"AllowDownload",	"Allow downloading package.");
INSERT INTO "Flags" VALUES("Package",	"0x00000002",	"ClientOptional",	"Purely optional for clients.");
INSERT INTO "Flags" VALUES("Package",	"0x00000004",	"ServerSideOnly",	"Only needed on the server side.");
INSERT INTO "Flags" VALUES("Package",	"0x00000008",	"BrokenLinks",	"Loaded from linker with broken import links.");
INSERT INTO "Flags" VALUES("Package",	"0x00000010",	"Unsecure",	"Not trusted.");
INSERT INTO "Flags" VALUES("Package",	"0x00008000",	"Need",	"Client needs to download this package.");		

/* Class */
INSERT INTO "Flags" VALUES("Class",	"0x00000001",	"Abstract",	"Class is abstract and can't be instantiated directly.");
INSERT INTO "Flags" VALUES("Class",	"0x00000002",	"Compiled",	"Script has been compiled successfully.");
INSERT INTO "Flags" VALUES("Class",	"0x00000004",	"Config",	"Load object configuration at construction time.");
INSERT INTO "Flags" VALUES("Class",	"0x00000008",	"Transient",	"This object type can't be saved; null it out at save time.");
INSERT INTO "Flags" VALUES("Class",	"0x00000010",	"Parsed",	"Successfully parsed.");
INSERT INTO "Flags" VALUES("Class",	"0x00000020",	"Localized",	"Class contains localized text.");
INSERT INTO "Flags" VALUES("Class",	"0x00000040",	"SafeReplace",	"Objects of this class can be safely replaced with default or NULL.");
INSERT INTO "Flags" VALUES("Class",	"0x00000080",	"RuntimeStatic",	"Objects of this class are static during gameplay.");
INSERT INTO "Flags" VALUES("Class",	"0x00000100",	"NoExport",	"Don't export to C++ header.");
INSERT INTO "Flags" VALUES("Class",	"0x00000200",	"Placeable",	"Can be placed in editor.");
INSERT INTO "Flags" VALUES("Class",	"0x00000400",	"PerObjectConfig",	"Handle object configuration on a per-object basis, rather than per-class.");
INSERT INTO "Flags" VALUES("Class",	"0x00000800",	"NativeReplication",	"Replication handled in C++.");
INSERT INTO "Flags" VALUES("Class",	"0x00001000",	"EditInlineNew",	"Allows an instance of this object to be created inline within UnrealEd.");
INSERT INTO "Flags" VALUES("Class",	"0x00002000",	"CollapseCategories",	"All categories will be collapsed to a single category.");

/* Property */
INSERT INTO "Flags" VALUES("Property",	"0x00000001",	"Edit",	"Property is user-settable in the editor.");
INSERT INTO "Flags" VALUES("Property",	"0x00000002",	"Const",	"Actor's property always matches class's default actor property.");
INSERT INTO "Flags" VALUES("Property",	"0x00000004",	"Input",	"Variable is writable by the input system.");
INSERT INTO "Flags" VALUES("Property",	"0x00000008",	"ExportObject",	"Object can be exported with actor.");
INSERT INTO "Flags" VALUES("Property",	"0x00000010",	"OptionalParm",	"Optional parameter (if CPF_Param is set).");
INSERT INTO "Flags" VALUES("Property",	"0x00000020",	"Net",	"Property is relevant to network replication.");
INSERT INTO "Flags" VALUES("Property",	"0x00000040",	"EditConstArray",	"");
INSERT INTO "Flags" VALUES("Property",	"0x00000080",	"Parm",	"Function/When call parameter.");
INSERT INTO "Flags" VALUES("Property",	"0x00000100",	"OutParm",	"Value is copied out after function call.");
INSERT INTO "Flags" VALUES("Property",	"0x00000200",	"SkipParm",	"Property is a short-circuitable evaluation function parm.");
INSERT INTO "Flags" VALUES("Property",	"0x00000400",	"ReturnParm",	"Return value.");
INSERT INTO "Flags" VALUES("Property",	"0x00000800",	"CoerceParm",	"Coerce args into this function parameter.");
INSERT INTO "Flags" VALUES("Property",	"0x00001000",	"Native",	"Property is native: C++ code is responsible for serializing it.");
INSERT INTO "Flags" VALUES("Property",	"0x00002000",	"Transient",	"Property is transient: shouldn't be saved, zero-filled at load time.");
INSERT INTO "Flags" VALUES("Property",	"0x00004000",	"Config",	"Property should be loaded/saved as permanent profile.");
INSERT INTO "Flags" VALUES("Property",	"0x00008000",	"Localized",	"Property should be loaded as localizable text.");
INSERT INTO "Flags" VALUES("Property",	"0x00010000",	"Travel",	"Property travels across levels/servers.");
INSERT INTO "Flags" VALUES("Property",	"0x00020000",	"EditConst",	"Property is uneditable in the editor.");
INSERT INTO "Flags" VALUES("Property",	"0x00040000",	"GlobalConfig",	"Load config from base class, not subclass.");
INSERT INTO "Flags" VALUES("Property",	"0x00100000",	"OnDemand",	"Object or dynamic array loaded on demand only.");
INSERT INTO "Flags" VALUES("Property",	"0x00200000",	"New",	"Automatically create inner object.");
INSERT INTO "Flags" VALUES("Property",	"0x00400000",	"NeedCtorLink",	"Fields need construction/destruction.");
INSERT INTO "Flags" VALUES("Property",	"0x00800000",	"NoExport",	"This will prevent the class from being exported automatically to the header file.");	
INSERT INTO "Flags" VALUES("Property",	"0x01000000",	"Button",	"?");	
INSERT INTO "Flags" VALUES("Property",	"0x02000000",	"Comment",	"Has serialized comment for UnrealEd property inspector.");	
INSERT INTO "Flags" VALUES("Property",	"0x04000000",	"EditInline",	"This object reference can be edited inline within UnrealEd's property inspector.");	
INSERT INTO "Flags" VALUES("Property",	"0x08000000",	"EdFindable",	"Allows this actor to be findable within the editor.");	
INSERT INTO "Flags" VALUES("Property",	"0x10000000",	"EditInlineUse",	"Similar to editinline, editinlineuse will also add a 'use' button for the property.");	
INSERT INTO "Flags" VALUES("Property",	"0x20000000",	"Deprecated",	"The compiler will print a warning.");	
INSERT INTO "Flags" VALUES("Property",	"0x40000000",	"EditInlineNotify",	"This will notify the outer object if the property is changed.");	

/* Object */
INSERT INTO "Flags" VALUES("Object",	"0x00000001",	"Transactional",	"Object is transactional.");
INSERT INTO "Flags" VALUES("Object",	"0x00000002",	"Unreachable",	"Object is not reachable on the object graph.");
INSERT INTO "Flags" VALUES("Object",	"0x00000004",	"Public",	"Object is visible outside its package.");
INSERT INTO "Flags" VALUES("Object",	"0x00000008",	"TagImp",	"Temporary import tag in load/save.");
INSERT INTO "Flags" VALUES("Object",	"0x00000010",	"TagExp",	"Temporary export tag in load/save.");
INSERT INTO "Flags" VALUES("Object",	"0x00000020",	"SourceModified",	"Modified relative to source files.");
INSERT INTO "Flags" VALUES("Object",	"0x00000040",	"TagGarbage",	"Check during garbage collection.");
INSERT INTO "Flags" VALUES("Object",	"0x00000080",	"Private",	"Can be accessed only from the class it's in.");
INSERT INTO "Flags" VALUES("Object",	"0x00000200",	"NeedLoad",	"During load, indicates object needs loading.");
INSERT INTO "Flags" VALUES("Object",	"0x00000400",	"HighlightedName",	"A hardcoded name which should be syntax-highlighted.");
INSERT INTO "Flags" VALUES("Object",	"0x00000400",	"EliminateObject",	"NULL out references to this during garbage collecion.");
INSERT INTO "Flags" VALUES("Object",	"0x00000800",	"InSingularFunc",	"In a singular function.");
INSERT INTO "Flags" VALUES("Object",	"0x00000800",	"RemappedName",	"Name is remapped.");
INSERT INTO "Flags" VALUES("Object",	"0x00001000",	"Suppress",	"Suppressed log name.");
INSERT INTO "Flags" VALUES("Object",	"0x00001000",	"StateChanged",	"Object did a state change.");
INSERT INTO "Flags" VALUES("Object",	"0x00002000",	"InEndState",	"Within an EndState call.");
INSERT INTO "Flags" VALUES("Object",	"0x00004000",	"Transient",	"Don't save object.");
INSERT INTO "Flags" VALUES("Object",	"0x00008000",	"Preloading",	"Data is being preloaded from file.");
INSERT INTO "Flags" VALUES("Object",	"0x00010000",	"LoadForClient",	"In-file load for client.");
INSERT INTO "Flags" VALUES("Object",	"0x00020000",	"LoadForServer",	"In-file load for client.");
INSERT INTO "Flags" VALUES("Object",	"0x00040000",	"LoadForEdit",	"In-file load for client.");
INSERT INTO "Flags" VALUES("Object",	"0x00080000",	"Standalone",	"Keep object around for editing even if unreferenced.");
INSERT INTO "Flags" VALUES("Object",	"0x00100000",	"NotForClient",	"Don't load this object for the game client.");
INSERT INTO "Flags" VALUES("Object",	"0x00200000",	"NotForServer",	"Don't load this object for the game server.");
INSERT INTO "Flags" VALUES("Object",	"0x00400000",	"NotForEdit",	"Don't load this object for the editor.");
INSERT INTO "Flags" VALUES("Object",	"0x00800000",	"Destroyed",	"Object Destroy has already been called.");
INSERT INTO "Flags" VALUES("Object",	"0x01000000",	"NeedPostLoad",	"Object needs to be postloaded.");
INSERT INTO "Flags" VALUES("Object",	"0x02000000",	"HasStack",	"Has execution stack.");
INSERT INTO "Flags" VALUES("Object",	"0x04000000",	"Native",	"Native (UClass only).");
INSERT INTO "Flags" VALUES("Object",	"0x08000000",	"Marked",	"Marked (for debugging).");
INSERT INTO "Flags" VALUES("Object",	"0x10000000",	"ErrorShutdown",	"ShutdownAfterError called.");
INSERT INTO "Flags" VALUES("Object",	"0x20000000",	"DebugPostLoad",	"For debugging Serialize calls.");
INSERT INTO "Flags" VALUES("Object",	"0x40000000",	"DebugSerialize",	"For debugging Serialize calls.");
INSERT INTO "Flags" VALUES("Object",	"0x80000000",	"DebugDestroy",	"For debugging Destroy calls.");


/* TABLE Snippets */
DROP TABLE IF EXISTS "Snippets";
CREATE TABLE "Snippets" 
(	"Name" TEXT NOT NULL
,	"Snippet" TEXT NOT NULL
);

INSERT INTO "Snippets" VALUES("RefItem",	"function RefItem(i) if i < 0 then return ImportTable.ImportItem[-i-1] elseif i > 0 then return ExportTable.ExportItem[i-1] end end");
INSERT INTO "Snippets" VALUES("RefItemName",	"function RefItemName(i) if i ~= 0 then return NameTable.NameItem[RefItem(Class).ObjectName].Name else return 'Class' end end");
INSERT INTO "Snippets" VALUES("ExportTypeName",	"function ExportTypeName(i,defname) local refname = RefItemName(i); local bExists = TypeExists(refname); if bExists then return refname else return defname end end");



/* TABLE Elements */
DROP TABLE IF EXISTS "Elements";
CREATE TABLE "Elements" 
(	"Parent" TEXT NOT NULL
,	"Type" TEXT NOT NULL
,	"Name" TEXT NOT NULL
,	"FriendlyName" TEXT NOT NULL
,	"PrintFormat" TEXT NOT NULL
);

/* File */
INSERT INTO "Elements" VALUES("File",	"object",	"'Header'", "", "");

/* Header */
INSERT INTO "Elements" VALUES("Header",	"DWORD",	"Signature", "", "");
INSERT INTO "Elements" VALUES("Header",	"assert",	"Signature == 0x9E2A83C1", "", "");
INSERT INTO "Elements" VALUES("Header",	"WORD",		"Version", "", "");
INSERT INTO "Elements" VALUES("Header",	"WORD",		"License", "", "");
INSERT INTO "Elements" VALUES("Header",	"DWORD",	"Flags", "", "");
INSERT INTO "Elements" VALUES("Header",	"object",	"'NameTable'", "", "");
INSERT INTO "Elements" VALUES("Header",	"object",	"'ExportTable'", "", "");
INSERT INTO "Elements" VALUES("Header",	"object",	"'ImportTable'", "", "");
INSERT INTO "Elements" VALUES("Header",	"GUID",		"GUID", "", "");
INSERT INTO "Elements" VALUES("Header",	"object",	"'GenerationTable'", "", "");

/* GenerationTable */
INSERT INTO "Elements" VALUES("GenerationTable",	"DWORD",	"Count", "", "");
INSERT INTO "Elements" VALUES("GenerationTable",	"array",	"'GenerationItem', Count", "", "");
INSERT INTO "Elements" VALUES("GenerationItem",	"DWORD",	"ExportCount", "", "");
INSERT INTO "Elements" VALUES("GenerationItem",	"DWORD",	"NameCount", "", "");


/* NameTable */
INSERT INTO "Elements" VALUES("NameTable",	"DWORD",	"Count", "", "");
INSERT INTO "Elements" VALUES("NameTable",	"DWORD",	"Offset", "", "");
INSERT INTO "Elements" VALUES("NameTable",	"offset",	"Offset", "", "");
INSERT INTO "Elements" VALUES("NameTable",	"array",	"'NameItem', Count", "", "");
INSERT INTO "Elements" VALUES("NameItem",	"IASCII",	"Name", "", "");
INSERT INTO "Elements" VALUES("NameItem",	"DWORD",	"Flags", "", "");

/* ImportTable */
INSERT INTO "Elements" VALUES("ImportTable",	"DWORD",	"Count", "", "");
INSERT INTO "Elements" VALUES("ImportTable",	"DWORD",	"Offset", "", "");
INSERT INTO "Elements" VALUES("ImportTable",	"offset",	"Offset", "", "");
INSERT INTO "Elements" VALUES("ImportTable",	"array",	"'ImportItem', Count", "", "");
INSERT INTO "Elements" VALUES("ImportItem",	"INDEX",	"ClassPackage", "", "");
INSERT INTO "Elements" VALUES("ImportItem",	"INDEX",	"Class", "", "");
INSERT INTO "Elements" VALUES("ImportItem",	"INT32",	"Package", "", "");
INSERT INTO "Elements" VALUES("ImportItem",	"INDEX",	"ObjectName", "", "");

/* ExportTable */
INSERT INTO "Elements" VALUES("ExportTable",	"DWORD",	"Count", "", "");
INSERT INTO "Elements" VALUES("ExportTable",	"DWORD",	"Offset", "", "");
INSERT INTO "Elements" VALUES("ExportTable",	"offset",	"Offset", "", "");
INSERT INTO "Elements" VALUES("ExportTable",	"array",	"'ExportItem', Count", "", "");
INSERT INTO "Elements" VALUES("ExportItem",	"INDEX",	"Class", "", "");
INSERT INTO "Elements" VALUES("ExportItem",	"INDEX",	"Super", "", "");
INSERT INTO "Elements" VALUES("ExportItem",	"INT32",	"Package", "", "");
INSERT INTO "Elements" VALUES("ExportItem",	"INDEX",	"ObjectName", "", "");
INSERT INTO "Elements" VALUES("ExportItem",	"DWORD",	"ObjectFlags", "", "0x%.8x");
INSERT INTO "Elements" VALUES("ExportItem",	"INDEX",	"SerialSize", "", "");
INSERT INTO "Elements" VALUES("ExportItem",	"include",	"'ExportItem.Serialized', SerialSize ~= 0", "", "");
INSERT INTO "Elements" VALUES("ExportItem.Serialized",	"INDEX",	"SerialOffset", "", "");
INSERT INTO "Elements" VALUES("ExportItem.Serialized",	"delay",	"'ExportItem.Serialized.DelayLoaded'", "", "");
INSERT INTO "Elements" VALUES("ExportItem.Serialized.DelayLoaded",	"object",	"'ExportObject'", "", "");

/* ExportObject */
INSERT INTO "Elements" VALUES("ExportObject",	"log",	"'-----------------------------------------------------------'", "", "");
INSERT INTO "Elements" VALUES("ExportObject",	"offset",	"SerialOffset, SerialOffset + SerialSize", "", "");
INSERT INTO "Elements" VALUES("ExportObject",	"object",	"'StateFrame', FlagMask(ObjectFlags,Flag('Object','HasStack')) ~= 0", "", "");
INSERT INTO "Elements" VALUES("ExportObject",	"loop",		"'Properties', Class ~= 0", "", "");
INSERT INTO "Elements" VALUES("ExportObject",	"include",	"'ExportObject.ClassData', GetOffset() < SerialOffset + SerialSize", "", "");
INSERT INTO "Elements" VALUES("ExportObject.ClassData",		"object",	"ExportTypeName(Class,'UnknownExportData')", "", "");
INSERT INTO "Elements" VALUES("ExportObject",	"log",	"'-----------------------------------------------------------'", "", "");

/* UnknownExportData */
INSERT INTO "Elements" VALUES("UnknownExportData",	"data",		"'UnknownData', SerialSize - (GetOffset() - SerialOffset)", "", "");
	
/* Properties */
INSERT INTO "Elements" VALUES("Properties",	"INDEX",	"Name", "", "");
INSERT INTO "Elements" VALUES("Properties",	"log",	"string.format('Name: %s', NameTable.NameItem[Name].Name)", "", "");
INSERT INTO "Elements" VALUES("Properties",	"break",	"NameTable.NameItem[Name].Name == 'None'", "", "");
INSERT INTO "Elements" VALUES("Properties",	"bitfield",	"'Properties.Info'", "Property info byte", "");
INSERT INTO "Elements" VALUES("Properties.Info",	"BYTE",	"Info", "", "");
INSERT INTO "Elements" VALUES("Properties.Info",	"0x0f",	"Type", "", "");
INSERT INTO "Elements" VALUES("Properties.Info",	"0x70",	"SizeType", "", "");
INSERT INTO "Elements" VALUES("Properties.Info",	"0x80",	"IsArray", "", "");
INSERT INTO "Elements" VALUES("Properties",	"include",	"'Properties.Debug', Info == 90", "", "");
INSERT INTO "Elements" VALUES("Properties.Debug",	"log",	"'PropertyDebug'", "", "");
INSERT INTO "Elements" VALUES("Properties",	"include",	"'Properties.StructName', Type == 10", "Struct type name", "");
INSERT INTO "Elements" VALUES("Properties.StructName",	"INDEX",	"StructType", "NameTable Index", "");
INSERT INTO "Elements" VALUES("Properties",	"switch",	"'Properties.Size', SizeType", "Property size", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x00",	"0x01",		"Size", "", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x10",	"0x02",		"Size", "", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x20",	"0x04",		"Size", "", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x30",	"0x0c",		"Size", "", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x40",	"0x10",		"Size", "", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x50",	"BYTE",		"Size", "", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x60",	"WORD",		"Size", "", "");
INSERT INTO "Elements" VALUES("Properties.Size.0x70",	"DWORD",	"Size", "", "");
INSERT INTO "Elements" VALUES("Properties",	"include",	"'Properties.ArrayCount', IsArray ~= 0 and Type ~= 3", "Property array", "");
INSERT INTO "Elements" VALUES("Properties.ArrayCount",	"PARRAY",	"ArrayCount", "", "");
INSERT INTO "Elements" VALUES("Properties",	"object",	"FlagName('PropertyType',Type)", "", "");

	
/* PropertyTypeByte */
INSERT INTO "Elements" VALUES("PropertyTypeByte",	"BYTE",	"Value", "", "");
	
/* PropertyTypeInt */
INSERT INTO "Elements" VALUES("PropertyTypeInt",	"INT32",	"Value", "", "");
	
/* PropertyTypeBool */
INSERT INTO "Elements" VALUES("PropertyTypeBool",	"log",	"string.format('Value = %d',IsArray)", "", "");
	
/* PropertyTypeFloat */
INSERT INTO "Elements" VALUES("PropertyTypeFloat",	"FLOAT",	"Value", "", "");
	
/* PropertyTypeObject */
INSERT INTO "Elements" VALUES("PropertyTypeObject",	"INDEX",	"ObjectType", "", "");

/* PropertyTypeName */
INSERT INTO "Elements" VALUES("PropertyTypeName",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeString */
INSERT INTO "Elements" VALUES("PropertyTypeString",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeClass */
INSERT INTO "Elements" VALUES("PropertyTypeClass",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeArray */
INSERT INTO "Elements" VALUES("PropertyTypeArray",	"data",	"'PropertyData', Size", "", "");
	
/* PropertyTypeStruct */
--INSERT INTO "Elements" VALUES("PropertyTypeStruct",	"object",	"NameTable.NameItem[StructType].Name", "", "");
INSERT INTO "Elements" VALUES("PropertyTypeStruct",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeVector */
INSERT INTO "Elements" VALUES("PropertyTypeVector",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeRotator */
INSERT INTO "Elements" VALUES("PropertyTypeRotator",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeStr */
INSERT INTO "Elements" VALUES("PropertyTypeStr",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeMap */
INSERT INTO "Elements" VALUES("PropertyTypeMap",	"data",	"'PropertyData', Size", "", "");

/* PropertyTypeFixedArray */
INSERT INTO "Elements" VALUES("PropertyTypeFixedArray",	"data",	"'PropertyData', Size", "", "");

/* StateFrame */
INSERT INTO "Elements" VALUES("StateFrame",	"INDEX",	"Node", "", "");
INSERT INTO "Elements" VALUES("StateFrame",	"INDEX",	"StateNode", "", "");
INSERT INTO "Elements" VALUES("StateFrame",	"QWORD",	"ProbeMask", "", "");
INSERT INTO "Elements" VALUES("StateFrame",	"INT32",	"LatentAction", "", "");
INSERT INTO "Elements" VALUES("StateFrame",	"include",	"'StateFrame.Node', StateNode ~= 0", "", "");
INSERT INTO "Elements" VALUES("StateFrame.Node",	"INDEX",	"Offset", "", "");
	
/* Field */
INSERT INTO "Elements" VALUES("Field",	"INDEX",	"SuperField", "", "");
INSERT INTO "Elements" VALUES("Field",	"INDEX",	"Next", "", "");
	
/* Const */
INSERT INTO "Elements" VALUES("Const",	"object",	"'Field'", "", "");
INSERT INTO "Elements" VALUES("Const",	"IASCII",	"Constant", "", "");
	
/* Enum */
INSERT INTO "Elements" VALUES("Enum",	"object",	"'Field'", "", "");
INSERT INTO "Elements" VALUES("Enum",	"INDEX",	"Count", "", "");
INSERT INTO "Elements" VALUES("Enum",	"array",	"'Enum.Item', Count", "", "");
INSERT INTO "Elements" VALUES("Enum.Item",	"INDEX",	"Name", "", "");
			
/* Property */
INSERT INTO "Elements" VALUES("Property",	"object",	"'Field'", "", "");
INSERT INTO "Elements" VALUES("Property",	"WORD",		"ArrayDimension", "", "");
INSERT INTO "Elements" VALUES("Property",	"WORD",		"ElementSize", "", "");
INSERT INTO "Elements" VALUES("Property",	"DWORD",	"PropertyFlags", "", "");
INSERT INTO "Elements" VALUES("Property",	"INDEX",	"Category", "", "");
INSERT INTO "Elements" VALUES("Property",	"include",		"'Property.Net', FlagMask(PropertyFlags,Flag('Property','Net')) ~= 0", "", "");
INSERT INTO "Elements" VALUES("Property.Net",	"WORD",		"ReplicationOffset", "", "");

/* ByteProperty */
INSERT INTO "Elements" VALUES("ByteProperty",	"include",	"'Property'", "", "");
INSERT INTO "Elements" VALUES("ByteProperty",	"INDEX",	"EnumType", "", "");

/* ObjectProperty */
INSERT INTO "Elements" VALUES("ObjectProperty",	"include",	"'Property'", "", "");
INSERT INTO "Elements" VALUES("ObjectProperty",	"INDEX",	"ObjectType", "", "");

/* FixedArrayProperty */
INSERT INTO "Elements" VALUES("FixedArrayProperty",	"include",	"'Property'", "", "");
INSERT INTO "Elements" VALUES("FixedArrayProperty",	"INDEX",	"Inner", "", "");
INSERT INTO "Elements" VALUES("FixedArrayProperty",	"INDEX",	"Count", "", "");

/* ArrayProperty */
INSERT INTO "Elements" VALUES("ArrayProperty",	"include",	"'Property'", "", "");
INSERT INTO "Elements" VALUES("ArrayProperty",	"INDEX",	"Inner", "", "");

/* MapProperty */
INSERT INTO "Elements" VALUES("MapProperty",	"include",	"'Property'", "", "");
INSERT INTO "Elements" VALUES("MapProperty",	"INDEX",	"Key", "", "");
INSERT INTO "Elements" VALUES("MapProperty",	"INDEX",	"Value", "", "");

/* ClassProperty */
INSERT INTO "Elements" VALUES("ClassProperty",	"include",	"'ObjectProperty'", "", "");
INSERT INTO "Elements" VALUES("ClassProperty",	"INDEX",	"Class", "", "");

/* StructProperty */
INSERT INTO "Elements" VALUES("StructProperty",	"include",	"'Property'", "", "");
INSERT INTO "Elements" VALUES("StructProperty",	"INDEX",	"StructType", "", "");

/* IntProperty */
INSERT INTO "Elements" VALUES("IntProperty",	"include",	"'Property'", "", "");

/* BoolProperty */
INSERT INTO "Elements" VALUES("BoolProperty",	"include",	"'Property'", "", "");

/* FloatProperty */
INSERT INTO "Elements" VALUES("FloatProperty",	"include",	"'Property'", "", "");

/* NameProperty */
INSERT INTO "Elements" VALUES("NameProperty",	"include",	"'Property'", "", "");

/* StrProperty */
INSERT INTO "Elements" VALUES("StrProperty",	"include",	"'Property'", "", "");

/* StringProperty */
INSERT INTO "Elements" VALUES("StringProperty",	"include",	"'Property'", "", "");

/* PointerProperty */
INSERT INTO "Elements" VALUES("PointerProperty",	"include",	"'Property'", "", "");

/* DelegateProperty */
INSERT INTO "Elements" VALUES("DelegateProperty",	"include",	"'Property'", "", "");
INSERT INTO "Elements" VALUES("DelegateProperty",	"INDEX",	"Event", "", "");
	
/* Struct */
INSERT INTO "Elements" VALUES("Struct",	"object",	"'Field'", "", "");
INSERT INTO "Elements" VALUES("Struct",	"INDEX",	"ScriptText", "", "");
INSERT INTO "Elements" VALUES("Struct",	"INDEX",	"Children", "", "");
INSERT INTO "Elements" VALUES("Struct",	"INDEX",	"FriendlyName", "", "");
INSERT INTO "Elements" VALUES("Struct",	"DWORD",	"Unknown", "", "");
INSERT INTO "Elements" VALUES("Struct",	"DWORD",	"Line", "", "");
INSERT INTO "Elements" VALUES("Struct",	"DWORD",	"TextPos", "", "");
INSERT INTO "Elements" VALUES("Struct",	"DWORD",	"ScriptSize", "", "");
INSERT INTO "Elements" VALUES("Struct",	"break",	"true", "Skip the rest of struct data, we need a decompiler to parse it", "");
INSERT INTO "Elements" VALUES("Struct",	"include",	"'Struct.Script', ScriptSize ~= 0", "", "");
INSERT INTO "Elements" VALUES("Struct.Script",	"data",	"'ByteCode', ScriptSize", "", "");
	
/* Function */
INSERT INTO "Elements" VALUES("Function",	"object",	"'Struct'", "", "");
INSERT INTO "Elements" VALUES("Function",	"include",	"'Function.ByteCode', Struct.ScriptSize ~= 0", "", "");
INSERT INTO "Elements" VALUES("Function.ByteCode",	"data",	"'StructScript', SerialSize - (2+1+4) - (GetOffset()-SerialOffset)", "", "");
INSERT INTO "Elements" VALUES("Function",	"offset",	"SerialOffset+SerialSize - (2+1+4)", "hackfix for unparsed struct", "");
INSERT INTO "Elements" VALUES("Function",	"WORD",		"NativeIndex", "", "");
INSERT INTO "Elements" VALUES("Function",	"BYTE",		"OperatorPrecedence", "", "");
INSERT INTO "Elements" VALUES("Function",	"DWORD",	"FunctionFlags", "", "");
	
/* State */
INSERT INTO "Elements" VALUES("State",	"object",	"'Struct'", "", "");
INSERT INTO "Elements" VALUES("State",	"skip",	"Struct.ScriptSize ~= 0, SerialOffset+SerialSize", "if struct wasn't parsed remaining data can't be either", "");
INSERT INTO "Elements" VALUES("State",	"QWORD",	"ProbeMask", "", "");
INSERT INTO "Elements" VALUES("State",	"QWORD",	"IgnoreMask", "", "");
INSERT INTO "Elements" VALUES("State",	"WORD",		"LabelTableOffset", "", "");
INSERT INTO "Elements" VALUES("State",	"DWORD",	"StateFlags", "", "");
	
/* Class */
-- TODO: if struct wasnt parsed, treat entire Class as binary data
INSERT INTO "Elements" VALUES("Class",	"object",	"'State'", "", "");
INSERT INTO "Elements" VALUES("Class",	"skip",	"State.Struct.ScriptSize ~= 0, SerialOffset+SerialSize", "if struct wasn't parsed remaining data can't be either", "");
INSERT INTO "Elements" VALUES("Class",	"DWORD",	"ClassFlags", "", "");
INSERT INTO "Elements" VALUES("Class",	"GUID",		"ClassGuid", "", "");
INSERT INTO "Elements" VALUES("Class",	"INDEX",	"DependenciesCount", "", "");
INSERT INTO "Elements" VALUES("Class",	"array",	"'Class.Dependencies', DependenciesCount", "", "");
INSERT INTO "Elements" VALUES("Class.Dependencies",	"INDEX",	"Class", "", "");
INSERT INTO "Elements" VALUES("Class.Dependencies",	"DWORD",	"Deep", "", "");
INSERT INTO "Elements" VALUES("Class.Dependencies",	"DWORD",	"ScriptTextCRC", "", "");
INSERT INTO "Elements" VALUES("Class",	"INDEX",	"PackageImportsCount", "", "");
INSERT INTO "Elements" VALUES("Class",	"array",	"'Class.Import', PackageImportsCount", "", "");
INSERT INTO "Elements" VALUES("Class.Import",	"INDEX",	"PackageImport", "", "");
INSERT INTO "Elements" VALUES("Class",	"INDEX",	"ClassWithin", "", "");
INSERT INTO "Elements" VALUES("Class",	"INDEX",	"ClassConfigName", "", "");
INSERT INTO "Elements" VALUES("Class",	"INDEX",	"HideCategoriesCount", "", "");
INSERT INTO "Elements" VALUES("Class",	"array",	"'Class.Hide', HideCategoriesCount", "", "");
INSERT INTO "Elements" VALUES("Class.Hide",	"INDEX",	"HideCategory", "", "");
INSERT INTO "Elements" VALUES("Class",	"loop",	"'Properties'", "", "");
	
/* ByteCode */
INSERT INTO "Elements" VALUES("ByteCode",	"assert",	"Eq(0,1)", "", "");
INSERT INTO "Elements" VALUES("ByteCode",	"INDEX",	"NoByteCode", "", "");
	
/* TextBuffer */
INSERT INTO "Elements" VALUES("TextBuffer",	"DWORD",	"Pos", "", "");
INSERT INTO "Elements" VALUES("TextBuffer",	"DWORD",	"Top", "", "");
INSERT INTO "Elements" VALUES("TextBuffer",	"IASCII",	"Text", "", "");
	
/* Palette */
INSERT INTO "Elements" VALUES("Palette",	"INDEX",	"ColorCount", "", "");
INSERT INTO "Elements" VALUES("Palette",	"array",	"'Palette.Color', ColorCount", "", "");
INSERT INTO "Elements" VALUES("Palette.Color",	"DWORD",	"Color", "", "");
	
/* Font */
INSERT INTO "Elements" VALUES("Font",	"INDEX",	"CharactersPerPage", "", "");
INSERT INTO "Elements" VALUES("Font",	"array",	"'Font.Char', CharactersPerPage", "", "");
INSERT INTO "Elements" VALUES("Font.Char",	"DWORD",	"X", "", "");
INSERT INTO "Elements" VALUES("Font.Char",	"DWORD",	"Y", "", "");
INSERT INTO "Elements" VALUES("Font.Char",	"DWORD",	"Width", "", "");
INSERT INTO "Elements" VALUES("Font.Char",	"DWORD",	"Height", "", "");
INSERT INTO "Elements" VALUES("Font.Char",	"BYTE",		"Texture", "", "");
INSERT INTO "Elements" VALUES("Font",	"INDEX",	"TexturesCount", "", "");
INSERT INTO "Elements" VALUES("Font",	"array",	"'Font.Texture', TexturesCount", "", "");
INSERT INTO "Elements" VALUES("Font.Texture",	"INDEX",	"Texture", "", "");
INSERT INTO "Elements" VALUES("Font",	"INDEX",	"Kerning", "", "");
INSERT INTO "Elements" VALUES("Font",	"DWORD",	"UNKNOWN0", "", "");
INSERT INTO "Elements" VALUES("Font",	"DWORD",	"UNKNOWN1", "", "");

/* Color */
INSERT INTO "Elements" VALUES("Color",	"BYTE",	"R", "", "");
INSERT INTO "Elements" VALUES("Color",	"BYTE",	"G", "", "");
INSERT INTO "Elements" VALUES("Color",	"BYTE",	"B", "", "");
INSERT INTO "Elements" VALUES("Color",	"BYTE",	"A", "", "");

/* Vector */
INSERT INTO "Elements" VALUES("Vector",	"FLOAT",	"X", "", "");
INSERT INTO "Elements" VALUES("Vector",	"FLOAT",	"Y", "", "");
INSERT INTO "Elements" VALUES("Vector",	"FLOAT",	"Z", "", "");

/* RangeVector */
INSERT INTO "Elements" VALUES("RangeVector",	"object",	"'Vector'", "Min", "");
INSERT INTO "Elements" VALUES("RangeVector",	"object",	"'Vector'", "Max", "");

/* BoundingBox */
INSERT INTO "Elements" VALUES("BoundingBox",	"object",	"'RangeVector'", "Box", "");
INSERT INTO "Elements" VALUES("BoundingBox",	"BYTE",		"Valid", "", "");

/* BoundingSphere */
INSERT INTO "Elements" VALUES("BoundingSphere",	"object",	"'Vector'", "Box", "");
INSERT INTO "Elements" VALUES("BoundingSphere",	"FLOAT",	"Radius", "", "");

/* Plane */
INSERT INTO "Elements" VALUES("Plane",	"FLOAT",	"X", "", "");
INSERT INTO "Elements" VALUES("Plane",	"FLOAT",	"Y", "", "");
INSERT INTO "Elements" VALUES("Plane",	"FLOAT",	"Z", "", "");
INSERT INTO "Elements" VALUES("Plane",	"FLOAT",	"W", "", "");

/* StaticMesh */
/*INSERT INTO "Elements" VALUES("StaticMesh",	"assert",	"false", "", "");
INSERT INTO "Elements" VALUES("StaticMesh",	"object",	"'BoundingBox'", "", "");
INSERT INTO "Elements" VALUES("StaticMesh",	"object",	"'BoundingSphere'", "", "");
INSERT INTO "Elements" VALUES("StaticMesh",	"INDEX",	"MaterialCount", "", "");
INSERT INTO "Elements" VALUES("StaticMesh",	"array",	"'StaticMesh.Material', MaterialCount", "", "");
INSERT INTO "Elements" VALUES("StaticMesh.Material",	"INDEX",	"MaterialCount", "", "");*/

/* Color */
INSERT INTO "Elements" VALUES("Texture",	"BYTE",	"MipMapCount", "", "");
INSERT INTO "Elements" VALUES("Texture",	"array",	"'Texture.MipMap', MipMapCount", "", "");
INSERT INTO "Elements" VALUES("Texture.MipMap",	"DWORD",	"MipEndOffset", "", "");
INSERT INTO "Elements" VALUES("Texture.MipMap",	"INDEX",	"MipSize", "", "");
INSERT INTO "Elements" VALUES("Texture.MipMap",	"data",	"'MipData', MipSize", "", "");
INSERT INTO "Elements" VALUES("Texture.MipMap",	"DWORD",	"Width", "", "");
INSERT INTO "Elements" VALUES("Texture.MipMap",	"DWORD",	"Height", "", "");
INSERT INTO "Elements" VALUES("Texture.MipMap",	"BYTE",	"WidthBits", "", "");
INSERT INTO "Elements" VALUES("Texture.MipMap",	"BYTE",	"HeightBits", "", "");

/* Rotator */
INSERT INTO "Elements" VALUES("Rotator",	"DWORD",	"Pitch", "", "");
INSERT INTO "Elements" VALUES("Rotator",	"DWORD",	"Yaw", "", "");
INSERT INTO "Elements" VALUES("Rotator",	"DWORD",	"Roll", "", "");


/* Property script codes:
	24 = float
	22 = int
	4a = property script

*/