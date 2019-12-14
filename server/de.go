package server

import (
	"fmt"
	"math/rand"
)

const (
	sphere fitnessFuncType = iota
	salomon
	rastrigin
	rosenbrock
	ackley
)

type fitnessFuncType int

func (f fitnessFuncType) String() string {
	return []string{"sphere", "salomon", "rastrigin", "rosenbrock", "ackley"}[f]
}

func init() {
	// var sphereFunc = fitnessFunction{ID: sphere, Dimensions: 50, MinValue: -1000, MaxValue: 1000}
	var salomonFunc = fitnessFunction{ID: salomon, Dimensions: 50, MinValue: -100, MaxValue: 100}
	// var rastriginFunc = fitnessFunction{ID: rastrigin, Dimensions: 50, MinValue: -5.12, MaxValue: 5.12}
	// var rosenbrockFunc = fitnessFunction{ID: rosenbrock, Dimensions: 50, MinValue: -1000, MaxValue: 1000}
	// var ackleyFunc = fitnessFunction{ID: ackley, Dimensions: 50, MinValue: -32, MaxValue: 32}

	fitnessFunc = salomonFunc
	populationLength = 50
	maxNumOfGenerations = 100
	agentPopulationsCount = 100
}

var agentPopulationsCount = 10
var fitnessFunc fitnessFunction
var populationLength = 100
var maxNumOfGenerations = 100

var agentsMap = make(map[int]agent)
var agentCount = 0

type agentRequest struct {
	AgentID    int        `json:"agentId"`
	Population population `json:"population"`
}

func (a agentRequest) String() string {
	return fmt.Sprintf("agentId: %d, population: %v", a.AgentID, a.Population)
}

type agentResponse struct {
	Population          population `json:"population"`
	Func                string     `json:"function"`
	Dimensions          int        `json:"dimensions"`
	MinValue            float64    `json:"minValue"`
	MaxValue            float64    `json:"maxValue"`
	AgentID             int        `json:"agentId"`
	CR                  float64    `json:"paramCR"`
	F                   float64    `json:"paramF"`
	MaxNumOfGenerations int        `json:"maxNumOfGenerations"`
}

func (a agentResponse) String() string {
	return fmt.Sprintf("population: %v, function: %q, dimensions: %v, minValue: %f, maxValue: %f, agentId: %d, CR: %f, F: %f", a.Population, a.Func, a.Dimensions, a.MinValue, a.MaxValue, a.AgentID, a.CR, a.F)
}

type agent struct {
	ID               int           `json:"id"`
	AgentResponse    agentResponse `json:"data"`
	GenerationNumber int           `json:"generationNumber"`
}

func (a agent) String() string {
	return fmt.Sprintf("id: %v, agentResponse: %v, generationNumber: %d", a.ID, a.AgentResponse, a.GenerationNumber)
}

func getCR() float64 {
	return getRandF64(0.8, 0.95)
}

func getF() float64 {
	return getRandF64(0.4, 0.6)
}

// fitnessFunction is a enum of available goal functions
type fitnessFunction struct {
	ID         fitnessFuncType
	Dimensions int
	MinValue   float64
	MaxValue   float64
}

// individual is a vector of elements
type individual []float64

// population is a vector of Individuals
type population []individual

func getRandInt(min, max int) int {
	return min + rand.Int()%(max-min)
}

func getRandF64(min, max float64) float64 {
	return min + rand.Float64()*(max-min)
}

func getRandomBool() bool {
	return getRandInt(0, 2) == 1
}

func populate(length int, f fitnessFunction) population {
	var population population

	for i := 0; i < length; i++ {
		vector := individual{}
		for j := 0; j < f.Dimensions; j++ {
			vector = append(vector, getRandF64(f.MinValue, f.MaxValue))
		}
		population = append(population, vector)
	}

	return population
}

func mutatePopulationWithRandomAgent(optimizedPopulation population) {
	randomAgentID := getRandomAgentID()
	randomAgent := agentsMap[randomAgentID]
	randomAgentPopulation := randomAgent.AgentResponse.Population

	mutatePoopulations(randomAgentPopulation, optimizedPopulation)

	randomAgent.AgentResponse.Population = randomAgentPopulation
	agentsMap[randomAgentID] = randomAgent
}

func mutatePoopulations(randomAgentPopulation, optimizedPopulation population) {
	for i := 0; i < populationLength; i++ {
		if getRandomBool() {
			randomAgentPopulation[i], optimizedPopulation[i] = optimizedPopulation[i], randomAgentPopulation[i]
		}
	}
}

func getRandomAgentID() int {
	keys := make([]int, len(agentsMap))

	i := 0
	for k := range agentsMap {
		keys[i] = k
		i++
	}

	return keys[getRandInt(0, i)]
}
