package unittestdemo

import "testing"

func TestIncr(t *testing.T) {
	var testcases = []struct {
		input int
		want int
	}{
		{1, 2},
		{2, 3},
		{0, 1},
		{-2, -1},
		{-3, -2},
	}
	for _, testcase := range testcases {
		if got := Incr(testcase.input); got != testcase.want {
			t.Errorf("Incr(%d) != %d", testcase.input, testcase.want)
		}
	}
}