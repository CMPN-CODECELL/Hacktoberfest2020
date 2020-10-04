# -*- coding: utf-8 -*-
import scrapy
from scrapy.crawler import CrawlerProcess
import json
import re
import bs4
from datetime import datetime

# Creating the issues spider
class PRSpider(scrapy.Spider):
    name = "pr"
    def __init__(self, *args, **kwargs):
        super(PRSpider, self).__init__(*args, **kwargs)
        url = kwargs.get('url')
        self.home_site = "https://github.com/"
        self.data=[]
        self.start_urls = [url]
        print(url)
        self.headers = {
                "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
                "Accept-Encoding": "gzip, deflate, br",
                "Accept-Language": "en-US,en;q=0.9",
                "Cache-Control": "no-cache",
                "Connection": "keep-alive",
                "Cookie": "_ga=GA1.2.454449396.1550070782; _octo=GH1.1.1426833685.1550070786; _device_id=adf2322aa9b4431468a67e1dba4909c7; user_session=sRre5MWeeM6yXnQ675cSdwd6efAVYnGey1nEYugVzFmcsGCU; __Host-user_session_same_site=sRre5MWeeM6yXnQ675cSdwd6efAVYnGey1nEYugVzFmcsGCU; logged_in=yes; dotcom_user=RitikMody; _gid=GA1.2.1221855545.1601667464; has_recent_activity=1; tz=Asia%2FCalcutta; _gat=1; _gh_sess=X56MT7ynrrFbt8HRWd2gHaDEUkQ80rvkTFZ3aLve5iIdzWE4hFRANycm3prsXjzqWlWjDePqLbTrRmW6gJTrxB7RNEQyQMaTL1yfGeJMDRDhsDFPQh4RUQvSdJupgjeU4VCtXMVKEpd5Gqq5IGAm1ZWSw3%2B5dTrxsSdwgNnZ0TacoLBAjpdCOjuMmzBFVbHOzBApLWnWrSOOSscYqsgyXQTNkGGZ34kolqvGa%2BTnOMDmPvQd8Enx9fMm%2Bh4ks7ikv8ZT4LnDzaJEOl2vTygZIyRIMzaxxqg3B2kUgL2PVkJcwbsx4iAjsWbDANPmG33PEtAqM%2BLBDGQ1whUp2FZDdwMSympWEjSB7GJ0BsK%2FQl54GXgQBJ0pjZL%2BykTKNXtWzGhuFrZhlGikxd2nzb3weGyydaUJCkB2fX2l%2FSKO8vJAIcJEyYfxPirACCM9nZFEJZlB5PE0ZHXmd8jIe5B9JKubHeCtk6pQmjYIkNkDnQBgGnOBrWy%2BpIXSUKYsNc%2F5Iv2I9O92N5%2Bj2b2%2BBdOPHrLQdbAROGWkwj1OhfTnJhIlYcM218uL5zSUYXmf%2BcqIkEbLdVkGJx2%2FZ0MUNxnkeWlEcr54zPoDYcQy%2BOoCitpaFDctBlgRVVOzfx6vSi90GMlAfkfI7D5ypOsYhiNaY%2F%2Bfc07CrIEwzPzveN2t3oajcV%2BMPocwksYWJLVEDbBledPN5XipjWOwsV%2BHYLbUabbHfVrSnZzIo2tlKISufrO0ZDdmcP6ks41wrH%2BuSTnqvm9YBn%2Ba5E%2B%2FStMiOKuEIvC57rq3N4oudQGoWNTwCvNrzC4tZAusQX9%2F9WXamuzQqho9bjdtL02jnJYwT7o%2B0JnhJtx37WqLPFhvfV7TaNAAhyNB%2B9hHt6MxMPX7DBdtHpLE6IXwOO%2FP3g9mBgHOCgF334eBxgeKe1egDz4OLUqUVwE0bcOjd6GMI3pR4l8TzGju8zKADzWzSMWlmabBtGYfT%2FPe2pjx1cti%2FU3UCRm9VXz3pU%2Fh2nD%2F5ZwWQo8xLShhQ6qc%2F8Y%3D--DwbE8HSUsO04UfAI--6PRsB6hBqmcAEvOpSIYYng%3D%3D",
                "Host": "github.com",
                "Pragma": "no-cache",
                "Sec-Fetch-Dest": "document",
                "Sec-Fetch-Mode": "navigate",
                "Sec-Fetch-Site": "none",
                "Sec-Fetch-User": "?1",
                "Upgrade-Insecure-Requests": "1",
                "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.121 Safari/537.36"
        }
    
    # Passing the start url and the headers to the parse function
    def start_requests(self):    
        yield scrapy.Request(url=self.start_urls[0], callback=self.parse, headers=self.headers )


    # The parse function if there is no pagination    
    def parse(self,response):
        pages = response.xpath('//*[@id="js-repo-pjax-container"]/div[2]/div/div/div[5]/div/a/text()').extract()
        if(len(pages)>0):
            last = int(pages[-2])
            print(last)
            urls = [self.start_urls[0]+"?page="+str(x)+"&q=is%3Aopen+is%3Apr" for x in range(1,last+1)]
            for url in urls:
                yield scrapy.Request(url=url, callback=self.parse_many, headers=self.headers )
        else:
            # Extracting divs containing the details about the issues 
            issues = response.xpath('//*[@id="js-repo-pjax-container"]/div[2]/div').extract_first()
            # Creating a soup to scrape the data from the divs
            k = bs4.BeautifulSoup(issues,"lxml").find_all("div")
            for issue in k:
                if issue.has_attr("data-id"):
                    date_time = datetime.strptime(re.sub("[a-zA-Z]"," ",issue.find('relative-time').get('datetime')).strip(" "),"%Y-%m-%d %H:%M:%S")
                    # Result dictionary
                    yield{
                        "title": issue.find('a',{"class":"link-gray-dark","data-hovercard-type":"pull_request"}).text,
                        "date" : date_time.date().strftime('%m/%d/%Y'),
                        "time" : date_time.time().strftime("%H:%M:%S"),
                        "author" : issue.find('a',{"data-hovercard-type":"user"}).text,
                        "number" : re.findall("#\d+",issue.find("span",{"class":"opened-by"}).text)[0]
                    }
                
            
    def parse_many(self,response):
        # Extracting divs containing the details about the issues 
        issues = response.xpath('//*[@id="js-repo-pjax-container"]/div[2]/div').extract_first()
        # Creating a soup to scrape the data from the divs
        k = bs4.BeautifulSoup(issues,"lxml").find_all("div")
        for issue in k:
            if issue.has_attr("data-id"):
                date_time = datetime.strptime(re.sub("[a-zA-Z]"," ",issue.find('relative-time').get('datetime')).strip(" "),"%Y-%m-%d %H:%M:%S")
                # Result dictionary
                yield{
                    "title": issue.find('a',{"class":"link-gray-dark","data-hovercard-type":"pull_request"}).text,
                    "date" : date_time.date().strftime('%m/%d/%Y'),
                    "time" : date_time.time().strftime("%H:%M:%S"),
                    "author" : issue.find('a',{"data-hovercard-type":"user"}).text,
                    "number" : re.findall("#\d+",issue.find("span",{"class":"opened-by"}).text)[0]
                }

# if __name__=="__main__":
#     process =CrawlerProcess()
#     process.crawl(PRSpider,url ='https://github.com/CMPN-CODECELL/Hacktoberfest2020/pulls')
#     process.start()
