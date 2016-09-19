## Requirements

```bash
sudo apt-get install wkhtmltopdf
```

## Setup & run

```bash
git clone git@github.com:alfonsocora/sinatra_pdf_test
cd sinatra_pdf_test
bundle
bundle exec ruby app.rb
```

Go to 'http://localhost:4567' with a browser.

bundle exec ruby app.rb -o 0.0.0.0 -p 3000
