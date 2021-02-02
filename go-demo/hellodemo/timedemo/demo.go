package timedemo

import (
	"fmt"
	"time"
)

func TimeDemo() {
	TimeTypeDemo()
	TimestampDemo()
	TimeOperationDemo()
	TimeFormatDemo()
	TimeParseDemo()
	TimeTickDemo()
}

func TimeTypeDemo() {
	now := time.Now()
	fmt.Printf("current time = %v\n", now)
	fmt.Printf("year=%d,month=%d, weekday=%d, day=%d, hour=%d, minute=%d, second=%d, nanosecond=%d\n", now.Year(), now.Month(), now.Weekday(), now.Day(), now.Hour(), now.Minute(), now.Second(), now.Nanosecond())
}

func TimestampDemo() {
	now := time.Now()
	fmt.Printf("timestamp-unix=%d, timestamp-unixnano=%d\n", now.Unix(), now.UnixNano())
}

func TimeOperationDemo() {
	now := time.Now()
	aHourLater := now.Add(time.Hour)
	fmt.Printf("add time: %v\n", aHourLater)
	fmt.Printf("time diff: %v\n", now.Sub(aHourLater))
	fmt.Printf("time after: %v\n", now.After(aHourLater))
	fmt.Printf("time before: %v\n", now.Before(aHourLater))
	fmt.Printf("time equal: %v\n", now.Equal(aHourLater))
}

func TimeFormatDemo() {
	now := time.Now()
	// 格式化的模板为Go的出生时间2006年1月2号15点04分 Mon Jan
	// 24小时制
	fmt.Println(now.Format("2006-01-02 15:04:05.000 Mon Jan"))
	// 12小时制
	fmt.Println(now.Format("2006-01-02 03:04:05.000 PM Mon Jan"))
	fmt.Println(now.Format("2006/01/02 15:04"))
	fmt.Println(now.Format("15:04 2006/01/02"))
	fmt.Println(now.Format("2006/01/02"))
}

func TimeParseDemo() {
	now := time.Now()
	fmt.Println(now)
	// 加载时区
	loc, err := time.LoadLocation("Asia/Shanghai")
	if err != nil {
		fmt.Println(err)
		return
	}
	// 按照指定时区和指定格式解析字符串时间
	timeObj, err := time.ParseInLocation("2006/01/02 15:04:05", "2019/08/04 14:15:20", loc)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(timeObj)
	fmt.Println(timeObj.Sub(now))
}

func TimeTickDemo() {
	ticker := time.Tick(time.Second)
	for i := range ticker {
		fmt.Printf("tick %v\n", i)
	}
}
