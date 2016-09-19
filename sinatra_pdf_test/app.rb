require 'sinatra'
require 'wicked_pdf'

configure do
  mime_type :pdf, 'application/pdf'
  WickedPdf.config = {
    :exe_path => Gem.bin_path('wkhtmltopdf-binary', 'wkhtmltopdf')
  }
end

get '/' do
  content_type :pdf
  WickedPdf.new.pdf_from_string('<h1 style="color:red">Hello There!</h1>')
end
