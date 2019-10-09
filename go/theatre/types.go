package theatre

type Performance struct {
	PlayID   string
	Audience int
}

type Play struct {
	Name string
	Type string
}

type Invoice struct {
	Customer     string
	Performances []Performance
}
