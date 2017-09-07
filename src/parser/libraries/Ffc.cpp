#include "../../precompiled.h"
#include "../Library.h"
#include "../LibraryHelper.h"

#include "../ByteCode.h"
#include "../Scope.h"

using namespace ZScript;
using namespace ZScript::Libraries;

Ffc const& Ffc::singleton()
{
	static Ffc const instance;
	return instance;
}

void Ffc::addTo(Scope& scope) const
{
	DataTypeSimple const* tVoid = &DataType::ZVOID;
	DataTypeSimple const* tBool = &DataType::BOOL;
	DataTypeSimple const* tFloat = &DataType::FLOAT;
	DataTypeClass const* tGame = &DataType::GAME;
	DataTypeClass const* tDebug = &DataType::DEBUG;
	DataTypeClass const* tScreen = &DataType::SCREEN;
	DataTypeClass const* tAudio = &DataType::AUDIO;
	DataTypeClass const* tLink = &DataType::_LINK;
	DataTypeClass const* tItemClass = &DataType::ITEMCLASS;
	DataTypeClass const* tItem = &DataType::ITEM;
	DataTypeClass const* tNpcClass = &DataType::NPCDATA;
	DataTypeClass const* tNpc = &DataType::NPC;
	DataTypeClass const* tFfc = &DataType::FFC;
	DataTypeClass const* tLWpn = &DataType::LWPN;
	DataTypeClass const* tEWpn = &DataType::EWPN;
	DataType const* tEnd = NULL;
	
	LibraryHelper lh(scope, REFFFC, tFfc);

	addPair(lh, DATA, tFloat, "Data");
	addPair(lh, FFSCRIPT, tFloat, "Script");
	addPair(lh, FCSET, tFloat, "CSet");
	addPair(lh, DELAY, tFloat, "Delay");
	addPair(lh, FX, tFloat, "X");
	addPair(lh, FY, tFloat, "Y");
	addPair(lh, XD, tFloat, "Vx");
	addPair(lh, YD, tFloat, "Vy");
	addPair(lh, XD2, tFloat, "Ax");
	addPair(lh, YD2, tFloat, "Ay");
	addPair(lh, FFFLAGSD, tBool, "Flags", 2); // XXX is this really 2?
	addPair(lh, FFTWIDTH, tFloat, "TileWidth");
	addPair(lh, FFTHEIGHT, tFloat, "TileHeight");
	addPair(lh, FFCWIDTH, tFloat, "EffectWidth");
	addPair(lh, FFCHEIGHT, tFloat, "EffectHeight");
	addPair(lh, FFLINK, tFloat, "Link");
	addPair(lh, FFMISCD, tFloat, "Misc", 16);
	addPair(lh, FFINITDD, tFloat, "InitD", 8);
	// addPair(lh, FFDD, tFloat, "D", 8);
	addPair(lh, FFCID, tFloat, "ID");

	// void ChangeFFCScript(ffc this, float script)
    {
	    Function& function = lh.addFunction(
			    tVoid, "ChangeFFCScript", tFloat, tEnd);
	    
        int label = function.getLabel();
        vector<Opcode *> code;
        //pop off the param
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
        code.push_back(first);
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OChangeFFCScriptRegister(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        function.giveCode(code);
    }
    
    // bool WasTriggered(ffc this)
    /*
    {
	    Function& function = lh.addFunction(tBool, "WasTriggered", tEnd);
	    
	    int label = function.getLabel();
	    vector<Opcode *> code;
	    //pop ffc
	    Opcode *first = new OPopRegister(new VarArgument(EXP2));
	    first->setLabel(label);
	    code.push_back(first);
	    //if ffc = -1, it is "this"
	    int thislabel = ScriptParser::getUniqueLabelID();
	    code.push_back(new OCompareImmediate(new VarArgument(EXP2), new LiteralArgument(-1)));
	    code.push_back(new OGotoTrueImmediate(new LabelArgument(thislabel)));
	    //if not this
	    //NOT POSSIBLE YET
	    //QUIT
	    code.push_back(new OQuit());
	    //if "this"
	    code.push_back(new OCheckTrig());
	    int truelabel = ScriptParser::getUniqueLabelID();
	    code.push_back(new OGotoTrueImmediate(new LabelArgument(truelabel)));
	    code.push_back(new OSetImmediate(new VarArgument(EXP1), new LiteralArgument(0)));
	    code.push_back(new OPopRegister(new VarArgument(EXP2)));
	    code.push_back(new OGotoRegister(new VarArgument(EXP2)));
	    Opcode *next = new OSetImmediate(new VarArgument(EXP1), new LiteralArgument(1));
	    next->setLabel(truelabel);
	    code.push_back(next);
	    code.push_back(new OPopRegister(new VarArgument(EXP2)));
	    code.push_back(new OGotoRegister(new VarArgument(EXP2)));
	    function.giveCode(code);
    }
    */
}
