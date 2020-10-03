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

@app.route('/issues')
def issue():
    args = request.args
    output_data.clear()
    url = 'https://github.com/CMPN-CODECELL/Hacktoberfest2020/issues'
    scrape_with_crochet(url=url,spider = issues.IssuesSpider)
    time.sleep(2)
    df = pd.DataFrame(output_data)
    df.to_csv("issues.csv",index=False)
    return jsonify(output_data)

@app.route('/prs')
def prs():
    args = request.args
    output_data.clear()
    url = 'https://github.com/CMPN-CODECELL/Hacktoberfest2020/pulls'
    scrape_with_crochet(url=url,spider = pr.PRSpider)
    time.sleep(2)
    df = pd.DataFrame(output_data)
    df.to_csv("pulls.csv",index=False)
    return jsonify(output_data)


@crochet.run_in_reactor
def scrape_with_crochet(url,spider):
    dispatcher.connect(_crawler_result, signal=signals.item_scraped)
    
    eventual = crawl_runner.crawl(spider, url = url)
    return eventual

def _crawler_result(item, response, spider):
    output_data.append(dict(item))

if __name__ == '__main__':
   app.run(debug = True)