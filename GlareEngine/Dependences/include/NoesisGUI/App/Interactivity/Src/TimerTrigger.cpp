////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsApp/TimerTrigger.h>
#include <NsGui/UIElementData.h>
#include <NsGui/IView.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>


using namespace Noesis;
using namespace NoesisApp;


////////////////////////////////////////////////////////////////////////////////////////////////////
TimerTrigger::TimerTrigger(): mTimer(-1), mTickCount(0)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TimerTrigger::~TimerTrigger()
{
    StopTimer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int TimerTrigger::GetMillisecondsPerTick() const
{
    return GetValue<int>(MillisecondsPerTickProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::SetMillisecondsPerTick(int ms)
{
    SetValue<int>(MillisecondsPerTickProperty, ms);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int TimerTrigger::GetTotalTicks() const
{
    return GetValue<int>(TotalTicksProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::SetTotalTicks(int ticks)
{
    SetValue<int>(TotalTicksProperty, ticks);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<TimerTrigger> TimerTrigger::Clone() const
{
    return StaticPtrCast<TimerTrigger>(Freezable::Clone());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<TimerTrigger> TimerTrigger::CloneCurrentValue() const
{
    return StaticPtrCast<TimerTrigger>(Freezable::CloneCurrentValue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Freezable> TimerTrigger::CreateInstanceCore() const
{
    return *new TimerTrigger();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::OnDetaching()
{
    StopTimer();

    ParentClass::OnDetaching();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::OnEvent()
{
    StopTimer();
    mTickCount = 0;
    StartTimer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::StartTimer()
{
    NS_ASSERT(mTimer < 0);

    IView* view = GetView();
    if (view != 0)
    {
        int nextTick = GetMillisecondsPerTick();
        mTimer = view->CreateTimer(nextTick, MakeDelegate(this, &TimerTrigger::OnTimerTick));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TimerTrigger::StopTimer()
{
    if (mTimer >= 0)
    {
        IView* view = GetView();
        if (view != 0)
        {
            view->CancelTimer(mTimer);
        }

        mTimer = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t TimerTrigger::OnTimerTick()
{
    int nextTick = GetMillisecondsPerTick();
    int totalTicks = GetTotalTicks();
    if (totalTicks > 0 && ++mTickCount >= totalTicks)
    {
        nextTick = 0; // stop timer
        mTimer = -1;
    }

    InvokeActions(0);

    return nextTick;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_BEGIN_COLD_REGION

NS_IMPLEMENT_REFLECTION(TimerTrigger)
{
    NsMeta<TypeId>("NoesisApp.TimerTrigger");

    DependencyData* data = NsMeta<DependencyData>(TypeOf<SelfClass>());
    data->RegisterProperty<int>(MillisecondsPerTickProperty, "MillisecondsPerTick",
        PropertyMetadata::Create(1000));
    data->RegisterProperty<int>(TotalTicksProperty, "TotalTicks",
        PropertyMetadata::Create(-1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
const DependencyProperty* TimerTrigger::MillisecondsPerTickProperty;
const DependencyProperty* TimerTrigger::TotalTicksProperty;