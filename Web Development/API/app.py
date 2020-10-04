import crochet
crochet.setup()

from flask import Flask,jsonify,request
from scrapy import signals
from scrapy.crawler import CrawlerRunner
from scrapy.signalmanager import dispatcher
from spiders import *
import time 
import pandas as pd

app = Flask(__name__)


output_data = []
crawl_runner = CrawlerRunner()


# Endpoint for issues
@app.route('/issues')
def issue():
    args = request.args
    output_data.clear()
    url = 'https://github.com/CMPN-CODECELL/Hacktoberfest2020/issues'
    # Passing the url to the spider
    scrape_with_crochet(url=url,spider = issues.IssuesSpider)
    time.sleep(2)
    df = pd.DataFrame(output_data)
    # Storing the results in a csv file
    df.to_csv("issues.csv",index=False)
    # Returning the response
    return jsonify(output_data)

# Endpoint for pull requests
@app.route('/prs')
def prs():
    args = request.args
    output_data.clear()
    url = 'https://github.com/CMPN-CODECELL/Hacktoberfest2020/pulls'
    # Passing the url to the spider
    scrape_with_crochet(url=url,spider = pr.PRSpider)
    time.sleep(2)
    df = pd.DataFrame(output_data)
    # Storing the results in a csv file
    df.to_csv("pulls.csv",index=False)
    # Returning the response
    return jsonify(output_data)

# Function to run the spider
@crochet.run_in_reactor
def scrape_with_crochet(url,spider):
    dispatcher.connect(_crawler_result, signal=signals.item_scraped)
    eventual = crawl_runner.crawl(spider, url = url)
    return eventual

# Function to store the yielded result in the ouyput list
def _crawler_result(item, response, spider):
    output_data.append(dict(item))

if __name__ == '__main__':
   app.run(debug = True)