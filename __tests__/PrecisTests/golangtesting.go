// Copyright 2019 NineFX Inc
// 30 August 2019
// Justin Baum
// golang.org/x/text/secure/precis testing vs bs-precis
package main

import (
	"encoding/json"
	"fmt"
	"golang.org/x/text/secure/precis"
	"io"
	"log"
	"os"
)

type testCase struct {
	Profile string `json:"profile"`
	Input   string `json:"input"`
	Output  string `json:"output"`
	Error   string `json:"error"`
}

func main() {
	f, err := os.Open("__tests__/PrecisTests/golden.json")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	d := json.NewDecoder(f)
	_, err = d.Token() //Don't really understand this
	if err != nil {
		log.Fatal(err)
	}

	var list []testCase

	for i := 0; d.More(); i++ {
		printSlice(list)
		var tc testCase
		switch err := d.Decode(&tc); err {
		case io.EOF:
			return
		case nil:
			list = append(list, runTest(tc))
		default:
			log.Fatal(err)
		}
	}
}

func runTest(tc testCase) testCase {
	var p *precis.Profile
	switch tc.Profile {
	case "Nickname":
		p = precis.Nickname
	case "UsernameCaseMapped", "UsernameCaseMapped:ToLower":
		p = precis.UsernameCaseMapped
	default:
		log.Fatal(nil)
	}
	out, err := p.String(tc.Input)
	errMessage := err.Error()
	results := &testCase{
		Input:   tc.Input,
		Profile: tc.Profile,
		Output:  out,
		Error:   errMessage,
	}
	return *results
}
func printSlice(s []testCase) {
	fmt.Printf("len=%d cap=%d %v\n", len(s), cap(s), s)
}
