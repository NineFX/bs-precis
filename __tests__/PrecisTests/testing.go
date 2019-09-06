// Command precisTests opens test/golden.json from the python version of Precis
// and attempts to run them against the Go version.
//
// Right now Python 3.7.4 appears to use Unicode Version 11.
// This means this program should be run with Go 1.13 to use the same version.
// This is gotip as of this gist.
//
// To install gotip try something like this:
//
//    go get golang.org/dl/gotip
//    gotip download
//    gotip run precisTests.go
package main

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"os"

	"golang.org/x/text/secure/precis"
	"golang.org/x/text/unicode/norm"
)

type testCase struct {
	Profile string `json:"profile"`
	Input   string `json:"input"`
	Output  string `json:"output"`
	Error   string `json:"error"`
}

func main() {
	f, err := os.Open("golden.json")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	d := json.NewDecoder(f)
	// Pop the open slice token so we can stream the elements instead of buffering
	// them all into memory.
	_, err = d.Token()
	if err != nil {
		log.Fatal(err)
	}
	for i := 0; d.More(); i++ {
		var tc testCase
		switch err := d.Decode(&tc); err {
		case io.EOF:
			return
		case nil:
		default:
			log.Fatal(err)
		}

		err = runTest(tc)
		if err != nil {
			log.Printf("Error in test %d: %v", i, err)
		}
	}
}

func runTest(tc testCase) error {
	var p *precis.Profile
	switch tc.Profile {
	case "Nickname":
		p = precis.Nickname
	case "NicknameCasePreserved":
		// TODO: one of these tests triggers a bug in the precis library that I need
		// to track down. Disable until such a time as I can fix it.
		return nil
	case "UsernameCaseMapped", "UsernameCaseMapped:ToLower":
		p = precis.UsernameCaseMapped
	case "UsernameCaseMapped:CaseFold":
		// This matches the definition of precis.UsernameCaseMapped except with
		// ToLower changed back to FoldCase like in previous versions of the precis
		// library.
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
	case "IdentifierClass", "FreeFormClass", "NicknameCaseMapped:ToLower",
		"NicknameCaseMapped:CaseFold", "NicknameCaseMapped":
		// TODO: figure out exactly what the Python library is doing with each of
		// these non-standard profiles and create a new profile that mimics their
		// behavior.
		return nil
	default:
		return fmt.Errorf("unexpected profile %q", tc.Profile)
	}

	out, err := p.String(tc.Input)
	// This error handling doesn't handle the case where we get an error that's
	// different than what's expected, but that will require a lot more
	// boilerplate.
	switch {
	case err == nil && tc.Error != "":
		return fmt.Errorf("Did not get expected error %q", tc.Error)
	case err != nil && tc.Error == "":
		return fmt.Errorf("Unexpected error: %v", err)
	}

	if out != tc.Output {
		return fmt.Errorf("Unexpected output when applying %s to %q (%0 [2]x): want=%q (%0 [3]x), got=%q (%0 [4]x)", tc.Profile, tc.Input, tc.Output, out)
	}
	return nil
}
