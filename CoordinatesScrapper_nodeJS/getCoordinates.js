const fs = require('fs')
let fileCoord = fs.readFileSync("./1.txt").toString()
let allLines = fileCoord.split("\n")
let allPoints = []
let allPointsXY = []
let setTrackPoints = new Set()
for (let i = 0; i < allLines.length; i++) {
    let line = allLines[i].split(" ")
    if (line[0] == "v") {
        line[line.length - 1] = line[line.length - 1].slice(0, line[line.length - 1].length - 2)
        // line[1] = line[1].slice(0, 3)
        // line[3] = line[3].slice(0, 3)
        if (!setTrackPoints.has(`${line[1].slice(0, 2)}_${line[2].slice(0, 2)}`)){
        setTrackPoints.add(`${line[3].slice(0, 3)}_${line[1].slice(0, 3)}`)
        // allPoints.push(`${line[1]}_${line[3]}`)
        allPointsXY.push([line[1],line[2]])
        }
        console.log(line)
    }

}

console.log(allPoints.length)
fs.writeFileSync("./2dPoints.txt", allPoints);

let code = ""


let maxXY= {}
let scanLine = ()=>{
    allPointsXY.forEach((point)=>{
        point[1] = Math.floor(point[1])
        maxXY[point[1]] = {
            "min":Infinity
        }
        maxXY[point[1]]["max"] = 0
    })
    allPointsXY.forEach((point)=>{
        point[1] = Math.floor(point[1])
        if(point[0]<maxXY[point[1]]["min"]){
            maxXY[point[1]]["min"] = point[0];
        }
        if(point[0]>maxXY[point[1]]["max"]){
            maxXY[point[1]]["max"] = point[0];
        }
    })
    let newAllXY = []
    for(let YCOORD in maxXY){
        newAllXY.push([maxXY[YCOORD]["min"],YCOORD])
        newAllXY.push([maxXY[YCOORD]["max"],YCOORD])
    }
    console.log("new length : " , newAllXY.length)
    return newAllXY
}

let writeCode = () => {
    let multiplier = 14
    // allPointsXY = scanLine()
    code = code + "glPushMatrix();\n"
    code = code + "glTranslatef(self->x,self->y,0);\n"
    code = code + "glBegin(GL_POINTS);\n"
    let minX= Infinity
    let maxX = 0
    let minY= Infinity
    let maxY = 0
    allPointsXY.forEach(point => {
        if(minX > point[0]){
            minX = point[0]
        }
        if(maxX < point[0]){
            maxX = point[0]
        }
        if(minY > point[1]){
            minY = point[1]
        }
        if(maxY < point[1]){
            maxY = point[1]
        }
        code = code + `glVertex2f(${point[0]*multiplier} - 60 ,${point[1]*multiplier} - 20);\n`
        // code = code + `glVertex3f(${point[0]},${point[1]});\n`
    })
    code = code + "glEnd();\n"
    code = code + "glTranslatef(-self->x,self->y,0);\n"
    code = code + "glPopMatrix();\n"
    // console.log(code)
    console.log("width : " + (maxX - minX)*multiplier + " height : " + (maxY-minY)*multiplier)
    fs.writeFileSync("./vertexCode.txt",code)
}

writeCode()

// scanLine()