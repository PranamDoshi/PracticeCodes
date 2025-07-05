package utils

import (
	"time"
)

func GetCurrentTimeStamp() int64 {
	/*
		Returns the timestamp in milliseconds since the Unix epoch.
	*/
	return time.Now().UnixMilli()
}
