// Fill out your copyright notice in the Description page of Project Settings.


#include "GeoData/BackgroundTimer.h"
#include <cstdio>
#include <chrono>

using namespace std;
BackgroundTimer::BackgroundTimer()
{
    /*
    std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

    if (async)
    {
        std::thread([after, task]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }).detach();
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(after));
        task();
    }*/
}

BackgroundTimer::~BackgroundTimer()
{
}
