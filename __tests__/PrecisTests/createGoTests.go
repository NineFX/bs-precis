// Copyright 2019 NineFX Inc.

package main

import (
	"encoding/json"
	"fmt"
	//"io"
	"golang.org/x/text/secure/precis"
	"golang.org/x/text/unicode/norm"
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

	_, err = d.Token()

	if err != nil {
		log.Fatal(err)
	}
	var testCases []testCase
	for i := 0; d.More(); i++ {
		var tc testCase
		d.Decode(&tc)
		var p *precis.Profile
		switch tc.Profile {
		case "Nickname":
			p = precis.Nickname
		case "UsernameCaseMapped", "UsernameCasEMapped:ToLower":
			p = precis.UsernameCaseMapped
		case "UsernameCaseMapped:CaseFold":
			p = precis.NewIdentifier(
				precis.FoldWidth,
				precis.FoldCase(),
				precis.Norm(norm.NFC),
				precis.BidiRule,
			)
		case "UsernameCasePreserved":
			p = precis.UsernameCasePreserved
		case "OpaqueString":
			p = precis.OpaqueString
		default:
			continue
		}
		out, err := p.String(tc.Input)
		tc.Output = out
		switch err {
		case nil:
			tc.Error = ""
		default:
			tc.Error = err.Error()
		}
		testCases = jsonMarshalling(tc, testCases)

	}
	encJson, _ := json.Marshal(testCases)
	fmt.Println(string(encJson))
}

// Not sure if this is exactly the golang way to do it, but giving it a shot
func jsonMarshalling(tc testCase, jsonList []testCase) []testCase {
	return append(jsonList, tc)
}
