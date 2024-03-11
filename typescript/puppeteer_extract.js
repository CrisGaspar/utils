import puppeteer from 'puppeteer';
import { writeFile } from "node:fs";
import { Buffer } from "node:buffer";
import { mkConfig, generateCsv, asString } from "export-to-csv";

const DEFAULT_URL = 'https://datatables.net/examples/basic_init/multiple_tables.html';

(async () => {
    // Launch the browser and open a new blank page
    const now = Date.now(); // Unix timestamp in milliseconds

    const browser = await puppeteer.launch();
    const page = await browser.newPage();
    await page.goto(DEFAULT_URL);

    const csvConfig = mkConfig({ useKeysAsHeaders: true });

    const tablesData = await page.evaluate(() => {
        const finalResults = []; // one entry per table

        // Find the tables that have headers
        const tables = Array.from(document.querySelectorAll('table:has(th)'));

        for(let tableIndex = 0; tableIndex < tables.length; ++tableIndex) {
            const tableElement = tables[tableIndex];
            const columns = Array.from(tableElement.querySelectorAll('thead tr th'));
            const columnNames = columns.map(elem => elem.innerText);
    
            const dataCells = Array.from(tableElement.querySelectorAll('tbody tr td'));
            const values = dataCells.map(td => td.innerText);
        
            let results = [];
            let currentRowObject = {};

            const columnsCount = columnNames.length;
            values.forEach((value, index) => {
                const columnIndex = index % columnsCount
                const name = columnNames[columnIndex];
                currentRowObject[name] = value;
                if (columnIndex === columnsCount - 1) {
                    results.push(currentRowObject);
                    currentRowObject = {}; 
                }
            });

            console.log(results);
            finalResults[tableIndex] = results;
        }
        return finalResults;
    });


    // Covert each table's data to csv and store in separate csv files
    for(let tableIndex = 0; tableIndex < tablesData.length; ++tableIndex) {
        const tableData = tablesData[tableIndex];
        const csv = generateCsv(csvConfig)(tableData);
        const filename = `results-${now}-table-${tableIndex+1}.csv`;
        const csvBuffer = new Uint8Array(Buffer.from(asString(csv)));

        // Write the csv file to disk
        writeFile(filename, csvBuffer, (err) => {
        if (err) throw err;
            console.log("file saved: ", filename);
        });
    }

    await browser.close();
})();