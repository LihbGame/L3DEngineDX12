////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SEPARATOR_H__
#define __GUI_SEPARATOR_H__


#include <NsCore/Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Control.h>


namespace Noesis
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Control that is used to separate items in items controls.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.separator.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Separator: public Control
{
    NS_DECLARE_REFLECTION(Separator, Control)
};

}


#endif
