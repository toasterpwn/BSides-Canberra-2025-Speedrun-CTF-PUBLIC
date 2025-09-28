const express = require("express");
const mysql = require('mysql2');

const conn = mysql.createConnection({
    host: 'db',
    user: 'dbuser',
    password: 'gonnawhackmykeyboard12389u12893huidsbr2938hr9823',
    database: 'flagdb'
});

const createFlag = async () => {
    conn.execute(`CREATE TABLE flags (id INT, flag VARCHAR(255))`)
    conn.execute(`INSERT INTO flags (flag) VALUES ('${process.env["FLAG"] ?? "FAKE{flag}"}')`)
    console.log("flag has been added to the db")
}

const checkFlag = async (flag) => {
    return new Promise((resolve, reject) => {
        conn.query('SELECT * FROM flags WHERE flag = ?', [flag], (err, rows) => {
            if (err) {
                reject(err);
            } else {
                resolve(rows);
            }
        });
    });
}

const app = express();
app.use(express.json());

app.post("/submit", async (req, res) => {
    const flag = req.body.flag;
    if (!flag) {
        res.json({"error": "missing 'flag' parameter"});
        return
    }
    const [results, _f] = await checkFlag(flag);
    if (results) {
        res.json({"message": "flag submission was successful!", "flag": results})
    } else {
        res.json({"message": "sorry, incorrect flag :.("})
    }
});

app.listen(1337, () => {
    createFlag()
    console.log("app is running")
});