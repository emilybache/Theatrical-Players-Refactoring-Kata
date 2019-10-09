package theatre_test

import (
	"bytes"
	"io/ioutil"
	"path"
	"strings"
	"testing"
)

// verify runs a list of sub-tests using input data from the "testdata" subdirectory named after the current test.
// All files with the suffix ".in.<inType>" are used as input for the test case function.
// The name before the suffix is used as the base name for the files this function uses.
//
// What the function returns will be compared to the file with suffix ".approved.<outType>".
// If its content does not match the result, or the file does not exist, the test fails and a file with suffix ".out.<outType>" is created.
//
// In case the function encounters an error, it can call Fatalf() on the passed test instance.
// To verify errors as approved data, be sure to include the error in your structured data.
//
// This function reports problems of file access, as well as a failure if no input files were found.
func verify(t *testing.T, inType string, outType string, testCase func(testing.TB, []byte) []byte) {
	t.Helper()
	datadir := path.Join("testdata", t.Name())
	files, err := ioutil.ReadDir(datadir)
	if err != nil {
		t.Fatalf("could not read test directory: %v", err)
	}
	fullInSuffix := ".in." + inType
	fullApprovedSuffix := ".approved." + outType
	inputData := make(map[string][]byte)
	approvedData := make(map[string][]byte)
	for _, file := range files {
		switch {
		case file.IsDir():
		case strings.HasSuffix(file.Name(), fullInSuffix):
			data, err := ioutil.ReadFile(path.Join(datadir, file.Name()))
			if err != nil {
				t.Errorf("failed to read input file %s: %v", file.Name(), err)
			}
			inputData[file.Name()] = data
		case strings.HasSuffix(file.Name(), fullApprovedSuffix):
			data, err := ioutil.ReadFile(path.Join(datadir, file.Name()))
			if err != nil {
				t.Errorf("failed to read approved file %s: %v", file.Name(), err)
			}
			approvedData[file.Name()] = data
		}
	}
	if len(inputData) == 0 {
		t.Fatalf("no input files in %s - is this the intent?", datadir)
	}
	for rangedInFilename, rangedInData := range inputData {
		inFilename := rangedInFilename
		inData := rangedInData
		t.Run(t.Name()+"/"+inFilename, func(t *testing.T) {
			result := testCase(t, inData)

			baseFilename := inFilename[:len(inFilename)-len(fullInSuffix)]
			expected, hasApproved := approvedData[baseFilename+fullApprovedSuffix]
			writeOutFile := false
			switch {
			case !hasApproved:
				t.Errorf("no approved data available (file %s not available)", baseFilename+fullApprovedSuffix)
				writeOutFile = true
			case !bytes.Equal(expected, result):
				t.Errorf("result does not match expectation")
				writeOutFile = true
			}
			if writeOutFile {
				err = ioutil.WriteFile(path.Join(datadir, baseFilename+".out."+outType), result, 0644)
				if err != nil {
					t.Errorf("failed to write output data: %v", err)
				}
			}
		})
	}
}
